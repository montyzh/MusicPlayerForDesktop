#include "mainwindow.h"
#include <QApplication>
#include "my_mci.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    return 0;
}
