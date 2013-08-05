#ifndef _NETWORK_REQ_H_
#define _NETWORK_REQ_H_

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace chat {
namespace net {

class NetworkAccessWrapper;

class NetworkRequest : public QObject, public QNetworkRequest {
    Q_OBJECT

    friend class NetworkAccessWrapper;

    signals:
        void finished(QNetworkReply *reply);

    public:
        NetworkRequest(QUrl url) : QNetworkRequest(url) {}
        void get();
        void post(QByteArray array);
        void onFinished(QNetworkReply *reply);

    private:

        static NetworkAccessWrapper _qNam;
        static QHash<QNetworkReply*, NetworkRequest*> _replyHash;
};

class NetworkAccessWrapper : public QNetworkAccessManager {
    Q_OBJECT

    public:
        NetworkAccessWrapper() : QNetworkAccessManager() {
            connect(this, SIGNAL(finished(QNetworkReply*)),  this, SLOT(onFinished(QNetworkReply*)));
        }
        Q_SLOT void onFinished(QNetworkReply *reply) {
           NetworkRequest::_replyHash[reply]->onFinished(reply);
        }
};

}
}

#endif
