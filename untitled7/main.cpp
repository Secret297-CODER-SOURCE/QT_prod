#include <QApplication>
#include "global_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Global_Window window;
    window.show();
    return app.exec();
}
