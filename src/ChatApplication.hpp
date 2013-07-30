#ifndef CHATAPP_H_
#define CHATAPP_H_

#include <QObject>

class ChatApplication : public QObject {
    Q_OBJECT

    public:
        ChatApplication(QObject *parent = 0);
        virtual ~ChatApplication() {};
        Q_SLOT void onClicked();

    private:
        QObject *_chatText;
};

#endif
