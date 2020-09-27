#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>

#include "gui/menubar.h"
#include "gui/climateguiwidget.h"

#include "data/climatedata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mMenuBar = std::make_unique<MenuBar>();
    setMenuBar(mMenuBar.get());

    mClimateData = new ClimateData();

    setCentralWidget(new ClimateGuiWidget(mClimateData));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("June", "June");
    settings.setValue("mainwindow/size", size());
    QMainWindow::closeEvent(event);
}


