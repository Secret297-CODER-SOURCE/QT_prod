#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "control_panel.h"
#include "сonnection.h"

class Global_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Global_Window(QWidget *parent = nullptr);

private slots:
    void handleConnect();
    void sendMessage();

private:
    ControlPanel* panelWindow = nullptr;
    Connection* connection;

    QLineEdit* ipEdit;
    QLineEdit* portEdit;
    QLineEdit* messageEdit;
    QPushButton* connectButton;
    QLabel* statusLabel;
};
