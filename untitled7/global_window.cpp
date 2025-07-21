#include "global_window.h"
#include <QFile>
#include <QDebug>
#include <QAbstractSocket>

Global_Window::Global_Window(QWidget *parent)
    : QWidget(parent), connection(new Connection())
{
    // UI-элементы
    ipEdit = new QLineEdit("127.0.0.1");
    portEdit = new QLineEdit("1234");
    messageEdit = new QLineEdit();
    connectButton = new QPushButton("Подключиться");
    statusLabel = new QLabel("Отключено");

    // Placeholder-тексты
    ipEdit->setPlaceholderText("IP адрес");
    portEdit->setPlaceholderText("Порт");
    messageEdit->setPlaceholderText("Введите сообщение");

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *ipPortLayout = new QHBoxLayout();

    ipPortLayout->addWidget(ipEdit);
    ipPortLayout->addWidget(portEdit);

    mainLayout->addLayout(ipPortLayout);
    mainLayout->addWidget(connectButton);
    mainLayout->addWidget(messageEdit);
    mainLayout->addWidget(statusLabel);

    // Подключение сигналов
    connect(connectButton, &QPushButton::clicked, this, &Global_Window::handleConnect);
    connect(messageEdit, &QLineEdit::returnPressed, this, &Global_Window::sendMessage);

    // Загрузка QSS-стиля
    QFile styleFile("style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        this->setStyleSheet(style);
    }

    setWindowTitle("TCP Клиент");
    resize(400, 200);
}

void Global_Window::handleConnect()
{
    QString ip = ipEdit->text();
    quint16 port = portEdit->text().toUShort();

    if (connection->connectToServer(ip, port)) {
        statusLabel->setText("🟢 Успешно подключено");
        qDebug() << "✔ Подключено к серверу";

        // Создаём и показываем панель управления
        panelWindow = new ControlPanel();
        panelWindow->show();

        // Закрываем окно подключения
        this->close();
    }
}

void Global_Window::sendMessage()
{
    QString message = messageEdit->text();
    if (connection->socket->state() == QAbstractSocket::ConnectedState) {
        connection->socket->write(message.toUtf8());
        messageEdit->clear();
    } else {
        qDebug() << "⚠ Невозможно отправить: нет подключения";
    }
}
