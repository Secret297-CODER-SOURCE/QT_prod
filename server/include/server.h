#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);
    ~Server();

    int start();
    void set_port(quint16 port);
    void stop();

private slots:
    void on_new_connection();
    void on_client_message();
    void on_client_disconnect();
    void on_client_error(QAbstractSocket::SocketError socket_error);
private:
    quint16 m_port;
    QList<QTcpSocket*> m_clients;
};

#endif // SERVER_H
