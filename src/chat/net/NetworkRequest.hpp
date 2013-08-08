#ifndef _NETWORK_REQ_H_
#define _NETWORK_REQ_H_

#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace chat {
namespace net {

class NetworkAccessWrapper;

class NetworkRequest : public QObject, public QNetworkRequest {
    Q_OBJECT

    friend class NetworkAccessWrapper;

    signals:

        void finished(chat::net::NetworkRequest *reply);

    public:

        NetworkRequest(QUrl url);
        void get();
        void post(QByteArray array);
        Q_SLOT void onFinished();
        int code(); 
        QByteArray data();

    private:

        QByteArray gUncompress(const QByteArray &data);

        static class NetworkAccessWrapper : public QNetworkAccessManager {
           public: 
                NetworkAccessWrapper(); 
           private:
                QNetworkDiskCache _cache;
        } _qNam;
        int _code;
        QByteArray _data;
};

}
}

#endif
