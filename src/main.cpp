#include <QApplication>

#include "chat/ContactsWindow.hpp"
#include "chat/ChatTranslator.hpp"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    chat::ChatTranslator translator(app);
    //new chat::ContactsWindow;

    return app.exec();
}
