#pragma once

#include <QObject>
#include <QTcpSocket>

class ClientHandler : public QObject {
    Q_OBJECT
public:
    ClientHandler(qintptr socketDescriptor, QObject* parent = nullptr);

public slots:
    void process();

signals:
    void finished();

private:
    qintptr socketDescriptor;
};
