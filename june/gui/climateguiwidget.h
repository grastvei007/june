#ifndef CLIMATEGUIWIDGET_H
#define CLIMATEGUIWIDGET_H

#include <QWidget>

class ClimateData;

namespace Ui {
class ClimateGuiWidget;
}

class ClimateGuiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClimateGuiWidget(ClimateData *aClimateData, QWidget *parent = nullptr);
    ~ClimateGuiWidget();

private slots:
    void onPowerSliderValueChanged(int aValue);
    void onRunningSliderValueChanged(int aValue);
    void onFanSliderValueChanged(int aValue);
    void onHeatSliderValueChanged(int aValue);

    void onFanValueChanged(int aValue);
    void onHeatValueChanged(int aValue);

private:
    Ui::ClimateGuiWidget *ui;
    ClimateData *mClimateData;
};

#endif // CLIMATEGUIWIDGET_H
