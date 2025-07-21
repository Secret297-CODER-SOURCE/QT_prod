#include "сonnection.h"

Connection::Connection() {
    socket = new QTcpSocket();
}

Connection::~Connection() {
    if (socket) {
        socket->close();
        delete socket;
    }
}

bool Connection::connectToServer(const QString& ip, quint16 port) {
    socket->connectToHost(ip, port);
    return socket->waitForConnected(3000);
}
