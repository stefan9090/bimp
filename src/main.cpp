#include "mainwindow.h"

#include "Logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    LOG_INFO("starting");

    Logging::initialize();

    QApplication app(argc, argv);

    MainWindow w;
    w.show();
    return QApplication::exec();
}
