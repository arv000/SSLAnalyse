#include "mainwindow.h"
#include <QApplication>
#include "tool/log_tools.h"
int main(int argc, char *argv[])
{
    qInstallMessageHandler(LogTools::myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
