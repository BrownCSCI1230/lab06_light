#include "mainwindow.h"

#include <QApplication>



/*
 * Entry point for the whole project.
 * The ONLY file you need to modify in this lab is lightmodel.cpp
 * You may want to read rgba.h and param.h first as they contain
 * some details about parameters, data structures you will use.
 */



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
