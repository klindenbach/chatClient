#include "chat/net/NetworkRequest.hpp"
#include <QDebug>
#include <zlib.h>

using chat::net::NetworkRequest;
using chat::net::NetworkAccessWrapper;

QNetworkAccessManager NetworkRequest::_qNam;

NetworkRequest::NetworkRequest(QUrl url) : QNetworkRequest(url) {
    setRawHeader("accept-encoding", "gzip");      
    setRawHeader("content-type", "application/x-www-form-urlencoded");
}

void NetworkRequest::get() {
    QNetworkReply *reply = _qNam.get(*this);
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
}

void NetworkRequest::post(QByteArray array) {
    QNetworkReply *reply = _qNam.post(*this, array);
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
}

void NetworkRequest::onFinished() {

    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

    _data = reply->readAll();

    if (reply->rawHeader("Content-Encoding") == "gzip") {
        _data = gUncompress(_data);
    }

    _code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (_code != 200) {
        qWarning() << "ERROR: " << _data;
    }

    emit finished(this);
}

QByteArray NetworkRequest::data() {
    return _data;
}

int NetworkRequest::code() {
    return _code;
}

/* From SO */
QByteArray NetworkRequest::gUncompress(const QByteArray &data) {

    if (data.size() <= 4) {
        qWarning("gUncompress: Input data is truncated");
        return QByteArray();
    }

    QByteArray result;

    int ret;
    z_stream strm;
    static const int CHUNK_SIZE = 1024;
    char out[CHUNK_SIZE];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = data.size();
    strm.next_in = (Bytef*)(data.data());

    ret = inflateInit2(&strm, 15 +  32); // gzip decoding
    if (ret != Z_OK)
        return QByteArray();

    // run inflate()
    do {
        strm.avail_out = CHUNK_SIZE;
        strm.next_out = (Bytef*)(out);

        ret = inflate(&strm, Z_NO_FLUSH);
        Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

        switch (ret) {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;     // and fall through
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            (void)inflateEnd(&strm);
            return QByteArray();
        }

        result.append(out, CHUNK_SIZE - strm.avail_out);
    } while (strm.avail_out == 0);

    // clean up and return
    inflateEnd(&strm);
    return result;
}
