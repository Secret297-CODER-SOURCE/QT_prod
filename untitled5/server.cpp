#include "server.h"
#include <QDebug>


Server::Server(QObject *parent) : QTcpServer(parent) {}

void Server::startServer()
{
    if (!listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server failed to start:" << errorString();
    } else {
        qDebug() << "Server started on port" << serverPort();
    }
}

void Server::stopServer()
{
    for (QTcpSocket* client : clients) {
        client->disconnectFromHost();
        client->close();
        client->deleteLater();
    }
    clients.clear();
    close();
    qDebug() << "Server stopped.";
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);
    clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
    qDebug() << "New client connected:" << socketDescriptor;


}

void Server::onClientDisconnected()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        clients.removeAll(client);
        client->deleteLater();
        qDebug() << "Client disconnected.";
    }
}
