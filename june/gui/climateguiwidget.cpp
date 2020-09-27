#include "climateguiwidget.h"
#include "ui_climateguiwidget.h"

#include <QSlider>

#include "../data/climatedata.h"

ClimateGuiWidget::ClimateGuiWidget(ClimateData *aClimateData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClimateGuiWidget),
    mClimateData(aClimateData)
{
    ui->setupUi(this);

    connect(ui->powerSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onPowerSliderValueChanged);
    connect(ui->runningSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onRunningSliderValueChanged);
    connect(ui->fanSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onFanSliderValueChanged);
    connect(ui->heatSlider, &QSlider::valueChanged, this, &ClimateGuiWidget::onHeatSliderValueChanged);
}

ClimateGuiWidget::~ClimateGuiWidget()
{
    delete ui;
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

}

void ClimateGuiWidget::onHeatSliderValueChanged(int aValue)
{

}
