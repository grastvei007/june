#ifndef FARMINGWIDGET_H
#define FARMINGWIDGET_H

#include <QWidget>
#include <QTime>

class FarmingData;

namespace Ui {
class FarmingWidget;
}

class FarmingWidget : public QWidget
{
    Q_OBJECT
public:
    FarmingWidget(FarmingData *data, QWidget *parent = nullptr);

private slots:
    void populateData();
    void onTemperatureSensorSelected(const QString &sensor);
    void onEnableTemperatureControl(Qt::CheckState state);
    void onEnableGrowLight(Qt::CheckState state);
    void onTemperatureChanged();
    void onGrowLightTimeChanged(QTime time);
    void onUpdateServerClicked(bool);

private:
    Ui::FarmingWidget *ui_;
    FarmingData *data_ = nullptr;
    bool isPopulatingData_ = false;
};

#endif // FARMINGWIDGET_H
