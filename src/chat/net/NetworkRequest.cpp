#include "chat/net/NetworkRequest.hpp"

using chat::net::NetworkRequest;
using chat::net::NetworkAccessWrapper;

NetworkAccessWrapper NetworkRequest::_qNam;
QHash<QNetworkReply*, NetworkRequest*> NetworkRequest::_replyHash;

void NetworkRequest::get() {
    QNetworkReply *reply = _qNam.get(*this);
    _replyHash[reply] = this;
}

void NetworkRequest::post(QByteArray array) {
    QNetworkReply *reply = _qNam.post(*this, array);
    _replyHash[reply] = this;
}

void NetworkRequest::onFinished(QNetworkReply *reply) {
    emit finished(reply);
}
