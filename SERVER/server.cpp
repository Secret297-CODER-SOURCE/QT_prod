#include "server.h"
#include "clienthandler.h"
#include <QDebug>

Server::Server(QObject* parent) : QTcpServer(parent) {}

bool Server::startServer(quint16 port) {
    return listen(QHostAddress::Any, port);
}

void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "[+] Подключение клиента, socket:" << socketDescriptor;

    QThread* thread = new QThread;
    ClientHandler* handler = new ClientHandler(socketDescriptor);

    handler->moveToThread(thread);

    connect(thread, &QThread::started, handler, &ClientHandler::process);
    connect(handler, &ClientHandler::finished, thread, &QThread::quit);
    connect(handler, &ClientHandler::finished, handler, &ClientHandler::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}
