#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    page_change();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::page_change()
{
    // Подключаем кнопки к переключению страниц
    connect(ui->btnPage1, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(0);  // Переключаем на страницу 0
    });

    connect(ui->btnPage2, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(1);  // Переключаем на страницу 1
    });

    // Можно добавить больше кнопок, если страниц больше
}


