#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QSysInfo>

#include "systemInfo.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr);
    ~Client();

    void set_connection_interval(int connection_interval_ms);
    void set_port(quint16 port);
    void set_host_address(QHostAddress host_address);
    void set_version(QString version);

    void send_message(const QString& message);

    int start();
private slots:
    void on_message();
    void on_connection_timeout();
    void on_connect();
    void on_disconnect();
    void on_error(QTcpSocket::SocketError socket_error);
private:
    int m_connection_interval_ms;
    quint16 m_port;
    QHostAddress m_host_address;
    QTcpSocket* m_socket;
    QTimer* m_connection_timer;
    QString m_version;
};

#endif // CLIENT_H
