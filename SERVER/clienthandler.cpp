#include "clienthandler.h"
#include <QDebug>

ClientHandler::ClientHandler(qintptr socketDescriptor, QObject* parent)
    : QObject(parent), socketDescriptor(socketDescriptor) {}

void ClientHandler::process() {
    QTcpSocket socket;
    if (!socket.setSocketDescriptor(socketDescriptor)) {
        qWarning() << "Ошибка дескриптора";
        emit finished();
        return;
    }

    qDebug() << "[Client]" << socketDescriptor << "подключён";

    while (socket.state() == QAbstractSocket::ConnectedState) {
        if (socket.waitForReadyRead(5000)) {
            QByteArray data = socket.readAll();
            qDebug() << "[Client" << socketDescriptor << "]:" << data;

            // Отправляем ответ
            socket.write("Echo: " + data);
            socket.flush();
        } else {
            qDebug() << "[Client" << socketDescriptor << "] отключился или timeout";
            break;
        }
    }

    socket.disconnectFromHost();
    socket.waitForDisconnected();
    emit finished();
}
