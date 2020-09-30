#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QListWidget>
#include <QDockWidget>
#include <QListWidgetItem>

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

    mListWidget = std::make_unique<QListWidget>(this);
    connect(mListWidget.get(), &QListWidget::itemClicked, this, &MainWindow::onListItemClicked);

    QDockWidget *listDockWidget = new QDockWidget();
    listDockWidget->setWidget(mListWidget.get());
    addDockWidget(Qt::LeftDockWidgetArea, listDockWidget);

    QListWidgetItem *climateItem = new QListWidgetItem("Climate");
    mListWidget->addItem(climateItem);
    mClimateData = new ClimateData();
    mCentralWidgets[climateItem] = std::make_unique<ClimateGuiWidget>(mClimateData);
    setCentralWidget(mCentralWidgets[climateItem].get());

    QListWidgetItem *triggerItem = new QListWidgetItem("Triggers");
    mListWidget->addItem(triggerItem);
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

}


