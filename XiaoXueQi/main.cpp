#include "mainwindow.h"

#include <QApplication>
#include "qtcp_server.h"
#include"mysql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySQL*sqlhand =MySQL::gethand();
    sqlhand->openDatabase();

    MainWindow w;
    w.show();
    return a.exec();
}
