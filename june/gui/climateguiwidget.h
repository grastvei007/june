#ifndef CLIMATEGUIWIDGET_H
#define CLIMATEGUIWIDGET_H

#include <QWidget>

#include <memory>
#include "ui_climateguiwidget.h"

class ClimateData;

namespace Ui {
class ClimateGuiWidget;
}

class ClimateGuiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClimateGuiWidget(ClimateData *aClimateData, QWidget *parent = nullptr);

private slots:
    void onPowerSliderValueChanged(int aValue);
    void onRunningSliderValueChanged(int aValue);
    void onFanSliderValueChanged(int aValue);
    void onHeatSliderValueChanged(int aValue);

    void onFanValueChanged(int aValue);
    void onHeatValueChanged(int aValue);

private:
    std::unique_ptr<Ui::ClimateGuiWidget> ui;
    ClimateData *mClimateData;
};

#endif // CLIMATEGUIWIDGET_H
