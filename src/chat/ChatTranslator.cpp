#include "ChatTranslator.hpp"

#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
#include <QSettings>
#include <QStringList>
#include <QApplication>

using chat::ChatTranslator;

namespace chat {

ChatTranslator::ChatTranslator(QApplication &app) {

    QString lang = getLanguage();

    _qtTranslator.load("qt_" + lang, 
                       QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&_qtTranslator);

    _appTranslator.load(lang);
    app.installTranslator(&_appTranslator);

    qDebug() << "Detected language is: " << lang;
}

QString ChatTranslator::getLanguage() {
    //OS X hack because Qt can't seem to pick up language
    QSettings settings("apple.com");
    QStringList sl = settings.value("AppleLanguages").toStringList();
    if (!sl.isEmpty()) {
        return sl.first().toLower().left(2);
    }
    return QLocale::languageToString(QLocale::system().language());
}

}


