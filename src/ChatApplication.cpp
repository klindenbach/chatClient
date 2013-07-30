#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>

#include "ChatApplication.hpp"

ChatApplication::ChatApplication(QObject *parent): QObject(parent) {
    QQmlEngine *engine = new QQmlEngine;
    QQmlComponent *component = new QQmlComponent(engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
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
}

void ChatApplication::onClicked() {
    static int a = 0;
    _chatText->setProperty("text", QString("Button pressed %1 times").arg(++a));
}
