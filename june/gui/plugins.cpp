#include "plugins.h"
#include "ui_plugins.h"

#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QNetworkRequest>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPushButton>
#include <QString>
#include <QHttpPart>
#include <QHttpMultiPart>

Plugins::Plugins(QNetworkAccessManager &nam, QNetworkRequestFactory& requestFactory, QWidget *parent) :
    networkAccessManager_(nam),
    networkRequestFactory_(requestFactory),
    QWidget(parent)
    , ui(new Ui::Plugins)
{
    ui->setupUi(this);

    connect(ui->load, &QPushButton::clicked, this, &Plugins::onLoadClicked);
    connect(ui->unload, &QPushButton::clicked, this, &Plugins::onUnloadClicked);
}

Plugins::~Plugins()
{
    delete ui;
}

void Plugins::onLoadClicked(bool)
{
    auto pluginName = ui->loadName->text();
    if(pluginName.isEmpty())
        return;

    QJsonObject value = {{"name", pluginName}};
    auto doc = QJsonDocument(value);

    auto request = networkRequestFactory_.createRequest("/plugin/load");
    networkAccessManager_.post(request, doc.toJson());
}

void Plugins::onUnloadClicked(bool)
{
    auto pluginName = ui->loadName->text();
    if(pluginName.isEmpty())
        return;

    QJsonObject value = {{"name", pluginName}};
    auto doc = QJsonDocument(value);

    auto request = networkRequestFactory_.createRequest("/plugin/unload");
    networkAccessManager_.post(request, doc.toJson());
}
