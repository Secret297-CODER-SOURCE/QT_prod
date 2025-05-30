#include <QCoreApplication>
#include "include/client.h"

// TODO: client.request_update(client.version);

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    Client client;

    client.set_connection_interval(5000);
    client.set_port(8080);
    client.set_host_address(QHostAddress::LocalHost);
    client.set_version("1.0.0");

    // in case if client hasn't started, client.start() will return 1
    // so if block will work
    if (client.start()) {
        qDebug() << "failed to start client";
        return 1;
    }

    return application.exec();
}
