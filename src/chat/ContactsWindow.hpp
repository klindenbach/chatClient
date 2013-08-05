#ifndef CONTACTS_WINDOW_H_
#define CONTACTS_WINDOW_H_

#include <QObject>
#include <QNetworkReply>

namespace chat {

class ContactsWindow : public QObject {
    Q_OBJECT

    public:

        static QString userName; //TO BE REMOVED... at some point

        ContactsWindow(QObject *parent = 0);
        Q_SLOT void onTriggered(QString user);
        Q_SLOT void onConversationID(QNetworkReply* reply);
        Q_SLOT void onUserChanged();

    private:
        
        QObject *_user;
};

}

#endif
