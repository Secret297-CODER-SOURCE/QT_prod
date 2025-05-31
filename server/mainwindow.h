#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/server.h"
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setServer(Server* srv);

private slots:
    void on_push();

private:
    Ui::MainWindow *ui;
    Server* server;
    void updateClientList();
};
#endif // MAINWINDOW_H
