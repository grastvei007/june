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
#include "gui/plugins.h"
#include "gui/centralwidgetfactory.h"

MainWindow::MainWindow(CentralWiddgetFactory &centralWidgetFactory, QNetworkAccessManager &nam, QNetworkRequestFactory &nrf, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkAccessManager_(nam),
    networkRequestFactory_(nrf),
    centralWidgetFactory_(centralWidgetFactory)
{
    ui->setupUi(this);


    mMenuBar = std::make_unique<MenuBar>(networkAccessManager_, networkRequestFactory_);
    setMenuBar(mMenuBar.get());

    mStatusBar = std::make_unique<StatusBar>(this);
    setStatusBar(mStatusBar.get());

    mListWidget = std::make_unique<QListWidget>(this);
    connect(mListWidget.get(), &QListWidget::itemClicked, this, &MainWindow::onListItemClicked);

    QDockWidget *listDockWidget = new QDockWidget();
    listDockWidget->setWidget(mListWidget.get());
    addDockWidget(Qt::LeftDockWidgetArea, listDockWidget);

    mListWidget->addItem("Climate");
    mListWidget->addItem("Triggers");
    mListWidget->addItem("pi-gpio");
    mListWidget->addItem("TagSocketBinding");
    mListWidget->addItem("LogValues");
    mListWidget->addItem("Farming");
	mListWidget->addItem("Gardena");

	setCentralWidgetByName("Triggers");
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
    auto name = aItem->text();
    setCentralWidgetByName(name);
}

void MainWindow::setCentralWidgetByName(const QString &name)
{
    auto *widget = centralWidgetFactory_.createWidget(name);
    if(!widget)
    {
        qDebug() << "Widget does not exist";
        return;
    }
    setCentralWidget(widget);
}
