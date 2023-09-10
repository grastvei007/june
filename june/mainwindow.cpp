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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    mTriggerData = new TriggerData();

    mListWidget->addItem("Climate");
    mListWidget->addItem("Triggers");

    centralWidgets_.try_emplace("Climate", std::make_shared<ClimateGuiWidget>(mClimateData));
    setCentralWidget(centralWidgets_["Climate"].get()); //new ClimateGuiWidget(mClimateData));
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
    if(!centralWidgets_.count(name))
    {
        if(name == "Climate")
            centralWidgets_.try_emplace("Climate", std::make_shared<ClimateGuiWidget>(mClimateData));
        else if(name == "Triggers")
            centralWidgets_.try_emplace("Triggers", std::make_shared<TriggerGuiWidget>(mTriggerData));

    }
    // prevent central widget from delete, TODO:fix crash in destruction
    auto centralWidget = takeCentralWidget();
    setCentralWidget(centralWidgets_[name].get());
}


