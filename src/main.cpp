#include <QApplication>

#include "chat/ChatApplication.hpp"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    chat::ChatApplication *chatApplication = new chat::ChatApplication;

    return app.exec();
}
