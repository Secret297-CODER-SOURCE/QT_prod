#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_push);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_push()
{
    QString cmd = ui->lineEdit->text().trimmed();
    if (cmd.isEmpty())
        return;

    QListWidgetItem* selectedItem = ui->clientListWidget->currentItem();
    if (!selectedItem) {
        ui->textEdit->append("No client selected");
        return;
    }

    QString clientText = selectedItem->text();
    QStringList parts = clientText.split(":");
    if (parts.size() != 2)
        return;

    QString ip = parts[0];
    quint16 port = parts[1].toUShort();

    for (QTcpSocket* client : server->clients()) {
        if (client->peerAddress().toString() == ip && client->peerPort() == port) {
            client->write(cmd.toUtf8() + "\n");
            client->flush();

            ui->textEdit->append("Sent to " + clientText + ": " + cmd);
            ui->lineEdit->clear();
            return;
        }
    }

    ui->textEdit->append("Client not found");
}

void MainWindow::setServer(Server* srv)
{
    server = srv;
    updateClientList();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClientList);
    timer->start(1000);
}

void MainWindow::updateClientList()
{
    if (!server)
        return;

    ui->clientListWidget->clear();

    for (QTcpSocket* client : server->clients()) {
        QString clientInfo = client->peerAddress().toString() + ":" + QString::number(client->peerPort());
        ui->clientListWidget->addItem(clientInfo);
    }
}
