#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QListWidget>
#include <QDockWidget>
#include <QListWidgetItem>
#include <QString>
#include <QDebug>

#include "gui/menubar.h"
#include "gui/statusbar.h"
#include "gui/climateguiwidget.h"
#include "gui/triggerguiwidget.h"

#include "data/climatedata.h"
#include "data/triggerdata.h"

MainWindow::MainWindow(TriggerGuiWidget *triggerGuiWidget, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    triggerGuiWidget(triggerGuiWidget)
{
    ui->setupUi(this);



    mMenuBar = std::make_unique<MenuBar>();
    setMenuBar(mMenuBar.get());

    mStatusBar = std::make_unique<StatusBar>();
    setStatusBar(mStatusBar.get());

    mListWidget = std::make_unique<QListWidget>(this);
    connect(mListWidget.get(), &QListWidget::itemClicked, this, &MainWindow::onListItemClicked);

    QDockWidget *listDockWidget = new QDockWidget();
    listDockWidget->setWidget(mListWidget.get());
    addDockWidget(Qt::LeftDockWidgetArea, listDockWidget);

    mClimateData = new ClimateData();

    mListWidget->addItem("Climate");
    mListWidget->addItem("Triggers");

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

void MainWindow::onListItemClicked(QListWidgetItem *aItem)
{
    QString name = aItem->text();
    if(name == "Climate")
        setCentralWidget(new ClimateGuiWidget(mClimateData));
    else if(name == "Triggers")
        setCentralWidget(triggerGuiWidget);
}


