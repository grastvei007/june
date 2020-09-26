#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/menubar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mMenuBar = std::make_unique<MenuBar>();
    setMenuBar(mMenuBar.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}
