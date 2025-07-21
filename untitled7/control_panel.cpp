#include "control_panel.h"

ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Панель RAT-контроля");
    resize(600, 400);

    QFile styleFile("style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        this->setStyleSheet(style);
    }

    QLabel* title = new QLabel("👾 Панель управления RAT’ником");
    title->setAlignment(Qt::AlignCenter);

    text = new QTextEdit(this);
    text->setFixedHeight(100);

    showText = new QLabel(this);

    QPushButton* dummyButton1 = new QPushButton("📂 Просмотр файлов");
    QPushButton* dummyButton2 = new QPushButton("🖥 Скриншот экрана");
    QPushButton* dummyButton3 = new QPushButton("💬 Отправить сообщение");
    QPushButton* dummyButton4 = new QPushButton("🔌 Отключиться");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(text);
    layout->addWidget(showText);
    layout->addWidget(dummyButton1);
    layout->addWidget(dummyButton2);
    layout->addWidget(dummyButton3);
    layout->addWidget(dummyButton4);
}
