#include <QApplication>

#include "chat/ContactsWindow.hpp"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    new chat::ContactsWindow;

    return app.exec();
}
