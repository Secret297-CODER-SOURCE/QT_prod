#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    if (!server.startServer(12345)) {
        qCritical() << "Не удалось запустить сервер";
        return -1;
    }

    return a.exec();
}
