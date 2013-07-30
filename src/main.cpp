#include <QApplication>

#include "ChatApplication.hpp"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    ChatApplication *chatApplication = new ChatApplication;

    return app.exec();
}
