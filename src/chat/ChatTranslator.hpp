#ifndef CHAT_TRANSLATOR_H_
#define CHAT_TRANSLATOR_H_

#include <QApplication>
#include <QTranslator>

namespace chat {

class ChatTranslator {
    public:
        ChatTranslator(QApplication &app);
        static QString getLanguage();
    private:
        QTranslator _qtTranslator;
        QTranslator _appTranslator;
};

}

#endif
