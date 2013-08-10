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

#include "chat/ConversationWindow.hpp"
#include "chat/ContactsWindow.hpp"
#include "chat/net/NetworkRequest.hpp"

using chat::ConversationWindow;
using chat::net::NetworkRequest;

ConversationWindow::ConversationWindow(QString conversationID, QObject *parent): QObject(parent), _conversationID(conversationID) {
    QQmlEngine *engine = new QQmlEngine(this);
    QQmlComponent *component = new QQmlComponent(engine, this);
    component->loadUrl(QUrl("qrc:/assets/ChatWindow.qml"));

    QObject *root;
    if (component->isReady()) {
        root = component->create();
        root->setProperty("title", tr("Conversation ID: ") + conversationID);
    }
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

    connect(root, SIGNAL(visibleChanged(bool)), this, SLOT(deleteLater()));
}

void ConversationWindow::onTimeOut() {
    QUrl url("http://chatServer:8080/chatServer/getMessages");
    QUrlQuery query;
    query.addQueryItem("after", "1");
    query.addQueryItem("conversation", _conversationID);
    url.setQuery(query);

    NetworkRequest *request = new NetworkRequest(url);
    request->get();

    connect(request, SIGNAL(finished(chat::net::NetworkRequest*)), this, SLOT(onMessages(chat::net::NetworkRequest*)));
    connect(request, SIGNAL(finished(chat::net::NetworkRequest*)), request, SLOT(deleteLater()));
}

void ConversationWindow::onMessages(NetworkRequest *reply) {

    QByteArray contents = reply->data();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(contents);
    QVariantList messages = jsonDoc.object()["msg"].toObject()["messages"].toArray().toVariantList();

    QString string;
    foreach (QVariant i, messages) {
        QVariantMap map = i.toMap();
        string += map["sender"].toString() + ": " + map["message"].toString() + "\n";
    }

    _chatText->setProperty("text", string);
}

void ConversationWindow::onClicked() {

    QUrl url("http://chatServer:8080/chatServer/postMessage");
    QUrlQuery query;
    query.addQueryItem("sender", chat::ContactsWindow::userName);
    query.addQueryItem("timeSent", QString::number(QDateTime::currentDateTime().toTime_t()));
    query.addQueryItem("conversation", _conversationID);
    url.setQuery(query);

    NetworkRequest *request = new NetworkRequest(url);
    request->post(_input->property("text").toByteArray());

    _input->setProperty("text", "");

    connect(request, SIGNAL(finished(chat::net::NetworkRequest*)), this, SLOT(onPostFinished(chat::net::NetworkRequest*)));
    connect(request, SIGNAL(finished(chat::net::NetworkRequest*)), request, SLOT(deleteLater()));
}

void ConversationWindow::onPostFinished(NetworkRequest *reply) {
    qDebug() << reply->data();
}
