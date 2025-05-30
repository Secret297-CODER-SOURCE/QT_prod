#include "../include/client.h"

Client::Client(QObject* parent)
    : QObject(parent), m_connection_timer(nullptr), m_socket(nullptr),
    m_connection_interval_ms(5000), m_port(0), m_host_address(QHostAddress::Null),
    m_version("")
{
    qDebug() << "client init";
}

Client::~Client()
{
    qDebug() << "client delete";
}

void Client::set_connection_interval(int connection_interval_ms)
{
    this->m_connection_interval_ms = connection_interval_ms;
}

void Client::set_port(quint16 port)
{
    this->m_port = port;
}

void Client::set_host_address(QHostAddress host_address)
{
    this->m_host_address = host_address;
}

void Client::set_version(QString version)
{
    this->m_version = version;
}

int Client::start()
{
    if (!m_connection_interval_ms) {
        qDebug() << "no connection interval set";
        return 1;
    }

    if (!m_port) {
        qDebug() << "no port set";
        return 1;
    }

    if (m_host_address.isNull()) {
        qDebug() << "no host address set";
        return 1;
    }

    qDebug() << "configuration set: " << m_host_address << "on port " << m_port << " with interval (ms)" << m_connection_interval_ms;
    qDebug() << "entering the connection loop";

    m_connection_timer = new QTimer(this);
    m_socket = new QTcpSocket(this);

    QObject::connect(m_socket, &QTcpSocket::connected, this, &Client::on_connect);
    QObject::connect(m_socket, &QTcpSocket::disconnected, this, &Client::on_disconnect);
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::on_message);
    QObject::connect(m_socket, &QTcpSocket::errorOccurred, this, &Client::on_error);

    QObject::connect(m_connection_timer, &QTimer::timeout, this, &Client::on_connection_timeout);
    m_connection_timer->setInterval(m_connection_interval_ms);
    m_connection_timer->start();

    return 0;
}

void Client::on_connection_timeout()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "socket is already in connected state";
        m_connection_timer->stop();
        return;
    }

    if (m_socket->state() == QAbstractSocket::ConnectingState) {
        qDebug() << "socket is in connecting state";
        m_connection_timer->stop();
        return;
    }

    m_socket->connectToHost(m_host_address, m_port);
}

void Client::on_connect()
{
    qDebug() << "connected";
    m_connection_timer->stop();
}

void Client::on_disconnect()
{
    qDebug() << "disconnected, entering the connection loop again";
    m_connection_timer->start();
}

void Client::on_error(QTcpSocket::SocketError socket_error)
{
    qDebug() << "socket error ocurred with state " << m_socket->state();
    qDebug() << "socket error: " << m_socket->errorString();
    qDebug() << "socket error code: " << socket_error;
}

void Client::on_message()
{
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data);

    qDebug() << "received message: " << message;

    if (message == "/info cpu")
    {
        QString response = get_cpu();
        send_message(response);
        return;
    }
    else if (message == "/info os")
    {
        QString response = get_os_name();
        send_message(response);
        return;
    }
    else if (message == "/info memory")
    {
        QString response = "";

        response += QString("Total: ") += get_total_memory();
        response += QString(" Avaible: ") += get_available_memory();
        response += QString(" Used: ") += get_used_memory();

        send_message(response);

        return;
    }
    else // unknown command
    {
        QString response = "!" + m_version;
        send_message(response);
        return;
    }
}

void Client::send_message(const QString& message)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        on_disconnect();
        return;
    }

    QByteArray data = message.toUtf8() + "\n";
    m_socket->write(data);
    m_socket->flush();

    qDebug() << "send message: " << message;
}
