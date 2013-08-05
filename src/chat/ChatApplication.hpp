#ifndef CHATAPP_H_
#define CHATAPP_H_

#include <QObject>
#include <QNetworkReply>

namespace chat {

class ChatApplication : public QObject {
    Q_OBJECT

    public:
        ChatApplication(QObject *parent = 0);
        virtual ~ChatApplication() {};
        Q_SLOT void onClicked();
        Q_SLOT void onPostFinished(QNetworkReply*);
        Q_SLOT void onMessages(QNetworkReply*);
        Q_SLOT void onTimeOut();

    private:
        QObject *_chatText;
        QObject *_input;
};

}

#endif
