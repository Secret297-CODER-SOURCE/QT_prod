#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QTextEdit>
#include <QLabel>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

public slots:
    void startServer();
    void stopServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onClientDisconnected();

private:
    QList<QTcpSocket*> clients;
};

#endif // SERVER_H
