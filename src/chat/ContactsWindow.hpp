#ifndef CONTACTS_WINDOW_H_
#define CONTACTS_WINDOW_H_

#include <QObject>

#include "chat/net/NetworkRequest.hpp"

namespace chat {

class ContactsWindow : public QObject {
    Q_OBJECT

    public:

        static QString userName; //TO BE REMOVED... at some point

        ContactsWindow(QObject *parent = 0);
        Q_SLOT void onTriggered(QString user);
        Q_SLOT void onConversationID(chat::net::NetworkRequest* reply);
        Q_SLOT void onUserChanged();

    private:
        
        QObject *_user;
};

}

#endif
