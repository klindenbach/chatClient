#ifndef CHATAPP_H_
#define CHATAPP_H_

#include <QObject>
#include <QNetworkReply>

#include "chat/net/NetworkRequest.hpp"

namespace chat {

class ConversationWindow : public QObject {
    Q_OBJECT

    public:
        ConversationWindow(QString conversationID, QObject *parent = 0);
        virtual ~ConversationWindow() {};
        Q_SLOT void onClicked();
        Q_SLOT void onPostFinished(chat::net::NetworkRequest*);
        Q_SLOT void onMessages(chat::net::NetworkRequest*);
        Q_SLOT void onTimeOut();

    private:
        QObject *_chatText;
        QObject *_input;
        QString _conversationID;
};

}

#endif
