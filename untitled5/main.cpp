#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QThread>
#include "server.h"
#include <QNetworkProxy>
#include <QTextEdit>
#include <QLabel>
QPushButton* btn = nullptr;
bool isStarted = false;
QThread thread;
Server* server = nullptr;

QTextEdit* text = nullptr;
QLabel* ShowText = nullptr;

void onClick()
{
    isStarted = !isStarted;
    btn->setText(isStarted ? "Finish" : "Start");
    if (isStarted) {
        server = new Server();
        server->moveToThread(&thread);

        QObject::connect(&thread, &QThread::started, server, &Server::startServer);
        QObject::connect(&thread, &QThread::finished, server, &QObject::deleteLater);

        thread.start();
    } else {
        if (server) {
            QMetaObject::invokeMethod(server, "stopServer", Qt::QueuedConnection);
            thread.quit();
            thread.wait();
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    QWidget widget;
    widget.setMinimumSize(500, 400);
    widget.setWindowTitle("gifarius");

    btn = new QPushButton("Start", &widget);
    btn->setGeometry(160, 120, 200, 60);
    QObject::connect(btn, &QPushButton::clicked, &onClick);

    text = new QTextEdit(&widget);
    text->setGeometry(160, 200, 200, 100);

    ShowText = new QLabel(&widget);
    ShowText->setGeometry(160, 300, 200, 100);


    widget.show();
    return app.exec();
}
