#include "../include/server.h"

Server::Server(QObject* parent) : QTcpServer(parent), m_port(0)
{
    qDebug() << "server init";
}

Server::~Server()
{
    qDebug() << "server delete";
}

void Server::set_port(quint16 port)
{
    this->m_port = port;
}

int Server::start()
{
    if (!m_port) {
        qDebug() << "no port set";
        return 1;
    }

    if (!listen(QHostAddress::Any, m_port)) {
        qDebug() << "failed to start server on port " << m_port;
        return 1;
    }

    qDebug() << "server started on port " << m_port;

    connect(this, &QTcpServer::newConnection, this, &Server::on_new_connection);

    return 0;
}

void Server::on_new_connection()
{
    QTcpSocket* client = nextPendingConnection();
    m_clients.append(client);

    qDebug() << "new connection from " << client->peerAddress().toString();

    connect(client, &QTcpSocket::readyRead, this, &Server::on_client_message);
    connect(client, &QTcpSocket::disconnected, this, &Server::on_client_disconnect);
    connect(client, &QTcpSocket::errorOccurred, this, &Server::on_client_error);

    //client->write(QString("/info cpu").toUtf8());
    //client->write(QString("/info os").toUtf8());
    client->write(QString("/info memory").toUtf8());
}

void Server::on_client_message()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        return;
    }

    QByteArray data = client->readAll();
    QString message = QString::fromUtf8(data);

    qDebug() << "new message from " << client->peerAddress().toString() << " : " << message;

    return;

    QString response_message;

    // work

    client->write(response_message.toUtf8() + "\n");
    client->flush();
}

void Server::on_client_disconnect()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        return;
    }

    qDebug() << "client " << client->peerAddress().toString() << " disconnected";

    m_clients.removeOne(client);
    client->deleteLater();
}

void Server::on_client_error(QAbstractSocket::SocketError socket_error)
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if (!client) {
        return;
    }

    qDebug() << "Client " << client->peerAddress().toString() << " error: " << client->errorString() << " with code: " << socket_error;

    m_clients.removeOne(client);
    client->deleteLater();
}

void Server::stop()
{
    for (QTcpSocket* client : m_clients)
    {
        client->disconnectFromHost();
        client->deleteLater();
    }
    m_clients.clear();
    close();
    qDebug() << "server stopped";
}
