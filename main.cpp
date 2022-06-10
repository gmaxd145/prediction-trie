#include "UI.h"
#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication Application(argc, argv);

    UI ui;
    ui.show();

    return QApplication::exec();
}