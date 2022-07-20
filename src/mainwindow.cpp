#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas2d.h"



/*
 * Basic Qt GUI operations.
 * You are NOT supposed to modify this file.
 */


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(768, 512+90);

    m_canvas = ui->Canvas;
    m_canvas->show();
    m_canvas->draw_load();
}

MainWindow::~MainWindow()
{
    delete ui;
}

