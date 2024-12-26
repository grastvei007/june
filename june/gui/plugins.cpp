#include "plugins.h"
#include "ui_plugins.h"

#include <QNetworkAccessManager>

Plugins::Plugins(QNetworkAccessManager &nam, QWidget *parent) :
    networkAccessManager_(nam),
    QWidget(parent)
    , ui(new Ui::Plugins)
{
    ui->setupUi(this);
}

Plugins::~Plugins()
{
    delete ui;
}
