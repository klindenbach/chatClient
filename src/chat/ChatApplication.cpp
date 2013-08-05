#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QUrlQuery>
#include <QDateTime>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QTimer>

#include "chat/ChatApplication.hpp"
#include "chat/net/NetworkRequest.hpp"

using chat::ChatApplication;
using chat::net::NetworkRequest;

ChatApplication::ChatApplication(QObject *parent): QObject(parent) {
    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent *component = new QQmlComponent(engine);
    component->loadUrl(QUrl("qrc:/assets/ChatWindow.qml"));

    QObject *root;
    if (component->isReady())
        root = component->create();
    else {
        qWarning() << component->errorString();
        return;
    }

    QObject *button = root->findChild<QObject*>("sendButton");
    if (button) {
        connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));
    }
    _chatText = root->findChild<QObject*>("chatText");
    _input = root->findChild<QObject*>("input");

    connect(_input, SIGNAL(accepted()), this, SLOT(onClicked()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start(1000);
}

void ChatApplication::onTimeOut() {
    QUrl url("http://localhost:8080/chatServer/getMessages");
    QUrlQuery query;
    query.addQueryItem("after", "1");
    url.setQuery(query);

    NetworkRequest *request = new NetworkRequest(url);
    request->get();

    connect(request, SIGNAL(finished(QNetworkReply*)), this, SLOT(onMessages(QNetworkReply*)));
    connect(request, SIGNAL(finished(QNetworkReply*)), request, SLOT(deleteLater()));
}

void ChatApplication::onMessages(QNetworkReply *reply) {

    QByteArray contents = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(contents);
    QVariantList messages = jsonDoc.object()["msg"].toObject()["messages"].toArray().toVariantList();

    QString string;
    foreach (QVariant i, messages) {
        QVariantMap map = i.toMap();
        string += map["sender"].toString() + ": " + map["message"].toString() + "\n";
    }

    _chatText->setProperty("text", string);
}

void ChatApplication::onClicked() {

    QUrl url("http://localhost:8080/chatServer/postMessage");
    QUrlQuery query;
    query.addQueryItem("sender", "konrad@EKCHAT.com");
    query.addQueryItem("timeSent", QString::number(QDateTime::currentDateTime().toTime_t()));
    query.addQueryItem("conversation", "1");
    url.setQuery(query);

    NetworkRequest *request = new NetworkRequest(url);
    request->post(_input->property("text").toByteArray());

    _input->setProperty("text", "");

    connect(request, SIGNAL(finished(QNetworkReply*)), this, SLOT(onPostFinished(QNetworkReply*)));
    connect(request, SIGNAL(finished(QNetworkReply*)), request, SLOT(deleteLater()));
}

void ChatApplication::onPostFinished(QNetworkReply *reply) {
    qDebug() << reply->readAll();
    qDebug() << reply->errorString();
}
