#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QString>

class Connection {
public:
    QTcpSocket* socket;

    Connection();
    ~Connection();

    bool connectToServer(const QString& ip, quint16 port);
};

#endif // CONNECTION_H
