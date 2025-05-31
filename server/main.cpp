#include "mainwindow.h"
#include "include/server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Server server;
    server.set_port(8080);
    if (server.start()) {
        qDebug() << "failed to start server";
        return 1;
    }

    w.setServer(&server);
    w.show();
    return a.exec();
}
