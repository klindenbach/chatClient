#include <QQmlEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include "chat/net/NetworkRequest.hpp"
#include "chat/ConversationWindow.hpp"
#include "chat/ContactsWindow.hpp"

using chat::ContactsWindow;
using chat::net::NetworkRequest;

QString ContactsWindow::userName;

ContactsWindow::ContactsWindow(QObject *parent): QObject(parent) {
    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent *component = new QQmlComponent(engine);
    component->loadUrl(QUrl("qrc:/assets/ContactsWindow.qml"));

    QObject *root;
    if (component->isReady())
        root = component->create();
    else {
        qWarning() << component->errorString();
        return;
    }

    ContactsWindow::userName = "emmanuel@EKCHAT.com";

    QObject *contactList = root->findChild<QObject*>("contactList");
    _user = root->findChild<QObject*>("userSelect");

    connect(contactList, SIGNAL(triggered(QString)), this, SLOT(onTriggered(QString)));
    connect(_user, SIGNAL(currentIndexChanged()), this, SLOT(onUserChanged()));
}

void ContactsWindow::onUserChanged() {
    QString currentUser = _user->property("currentText").toString();
    qDebug() << "Current user changed: " << currentUser;
    ContactsWindow::userName = currentUser;
    
}

void ContactsWindow::onTriggered(QString user) {

    QUrl url("http://chatServer:8080/chatServer/getConversationID");
    QUrlQuery query;
    query.addQueryItem("user1", user);
    query.addQueryItem("user2", _user->property("currentText").toString());
    url.setQuery(query);

    NetworkRequest *request = new NetworkRequest(url);
    request->get();

    connect(request, SIGNAL(finished(chat::net::NetworkRequest*)), this, SLOT(onConversationID(chat::net::NetworkRequest*)));
    connect(request, SIGNAL(finished(chat::net::NetworkRequest*)), request, SLOT(deleteLater()));
}

void ContactsWindow::onConversationID(NetworkRequest *reply) {
    QByteArray contents = reply->data();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(contents);
    QString conversationID = jsonDoc.object()["msg"].toString();

    if (conversationID != "0") {
        new chat::ConversationWindow(conversationID, this);
    }
    else {
        qWarning() << "No such conversation";
    }
}
