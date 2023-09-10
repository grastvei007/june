#include "climateguiwidget.h"


#include <QSlider>

#include "../data/climatedata.h"

ClimateGuiWidget::ClimateGuiWidget(ClimateData *aClimateData, QWidget *parent) :
    QWidget(parent),
    //    ui(new Ui::ClimateGuiWidget),
    mClimateData(aClimateData)
{
    ui = std::make_unique<Ui::ClimateGuiWidget>();
    ui->setupUi(this);

    connect(ui->powerSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onPowerSliderValueChanged);
    connect(ui->runningSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onRunningSliderValueChanged);
    connect(ui->fanSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onFanSliderValueChanged);
    connect(ui->heatSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onHeatSliderValueChanged);

    connect(mClimateData, &ClimateData::powerOnValueChanged, [this](bool value){
       ui->powerSlider->setValue(value);
    });

    connect(mClimateData, &ClimateData::fanValueChanged, [this](int value){
        ui->fanSlider->setValue(value);
    });

    connect(mClimateData, &ClimateData::heatValueChanged, [this](int value){
        ui->heatSlider->setValue(value);
    });

    connect(mClimateData, &ClimateData::temeratureInsideValueChange, [this](double value){
        ui->indoor->clear();
        ui->indoor->setText(QString::number(value) + "C");
    });

    connect(mClimateData, &ClimateData::temperaturOutdoorValueChange, [this](double value){
        ui->outside->clear();
        ui->outside->setText(QString::number(value) + "C");
    });
}


void ClimateGuiWidget::onPowerSliderValueChanged(int aValue)
{
    bool value = aValue;
    mClimateData->setPower(value);
}

void ClimateGuiWidget::onRunningSliderValueChanged(int aValue)
{
    bool value = aValue;
    mClimateData->setRunning(value);
}

void ClimateGuiWidget::onFanSliderValueChanged(int aValue)
{
    mClimateData->setFan(aValue);
}

void ClimateGuiWidget::onHeatSliderValueChanged(int aValue)
{
    mClimateData->setHeat(aValue);
}

void ClimateGuiWidget::onFanValueChanged(int aValue)
{
    ui->fanSlider->setValue(aValue);
}

void ClimateGuiWidget::onHeatValueChanged(int aValue)
{
    ui->heatSlider->setValue(aValue);
}
