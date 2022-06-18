#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas2d.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(768, 512+90);

    m_canvas = ui->Canvas;
    m_canvas->show();
    m_canvas->draw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

