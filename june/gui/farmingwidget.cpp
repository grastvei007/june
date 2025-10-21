#include "farmingwidget.h"

#include "ui_farmingwidget.h"

#include "data/farmingdata.h"

FarmingWidget::FarmingWidget(FarmingData *data, QWidget *parent) :
    QWidget(parent),
    data_(data),
    ui_(new Ui::FarmingWidget)
{
    ui_->setupUi(this);

    auto sensors = data_->availableTemperatureSensors();
    sensors.push_front("none");
    ui_->temperatureSensors->addItems(sensors);

    ui_->growLightOn->setDisplayFormat("hh:mm");
    ui_->growLightOff->setDisplayFormat("hh:mm");

    connect(data, &FarmingData::dataReady, this, &FarmingWidget::populateData);
    data->fetchFromServer();

    connect(ui_->temperatureSensors,
            &QComboBox::currentTextChanged,
            this,
            &FarmingWidget::onTemperatureSensorSelected);
    connect(ui_->enableDirtTemperatur,
            &QCheckBox::checkStateChanged,
            this,
            &FarmingWidget::onEnableTemperatureControl);
    connect(ui_->enableGrowLight,
            &QCheckBox::checkStateChanged,
            this,
            &FarmingWidget::onEnableGrowLight);
    connect(ui_->dirtTemperature,
            &QLineEdit::editingFinished,
            this,
            &FarmingWidget::onTemperatureChanged);
    connect(ui_->growLightOn, &QTimeEdit::timeChanged, this, &FarmingWidget::onGrowLightTimeChanged);
    connect(ui_->growLightOff,
            &QTimeEdit::timeChanged,
            this,
            &FarmingWidget::onGrowLightTimeChanged);
    connect(ui_->update, &QPushButton::clicked, this, &FarmingWidget::onUpdateServerClicked);
}

void FarmingWidget::populateData()
{
    isPopulatingData_ = true;

    ui_->enableDirtTemperatur->setCheckState(
        data_->isSeedHeatingEnabled() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    ui_->enableGrowLight->setCheckState(
        data_->isTurnOffGrowLightEnabled() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    double onSeedTemperature = data_->seedHeatingOn();
    double offSeedTemperature = data_->seedHeatingOff();
    double seedTargetTemperature = (offSeedTemperature - onSeedTemperature) / 2.
                                   + onSeedTemperature;
    ui_->dirtTemperature->clear();
    ui_->dirtTemperature->setText(QString::number(seedTargetTemperature));

    ui_->growLightOn->setTime(data_->turnOnGrowLight());
    ui_->growLightOff->setTime(data_->turnOffGrowLight());

    ui_->temperatureSensors->setCurrentText(data_->seedTemperatureSensor());

    isPopulatingData_ = false;
}

void FarmingWidget::onTemperatureSensorSelected(const QString &sensor)
{
    if (isPopulatingData_ || sensor == "none")
        return;

    data_->setTemperatureSensor(sensor);
}

void FarmingWidget::onEnableTemperatureControl(Qt::CheckState state)
{
    if (isPopulatingData_ || state == Qt::CheckState::PartiallyChecked)
        return;

    bool checked = (state == Qt::CheckState::Checked) ? true : false;
    data_->enableSeedControl(checked);
}

void FarmingWidget::onEnableGrowLight(Qt::CheckState state)
{
    if (isPopulatingData_ || state == Qt::CheckState::PartiallyChecked)
        return;

    bool checked = (state == Qt::CheckState::Checked) ? true : false;
    data_->enableGrowLight(checked);
}

void FarmingWidget::onTemperatureChanged()
{
    if (isPopulatingData_)
        return;

    bool ok;
    double value = ui_->dirtTemperature->text().toDouble(&ok);
    if (isPopulatingData_ || !ok)
        return;
    data_->setTempeperature(value);
}

void FarmingWidget::onGrowLightTimeChanged(QTime time)
{
    Q_UNUSED(time);
    if (isPopulatingData_)
        return;

    int on = ui_->growLightOn->time().msecsSinceStartOfDay();
    int off = ui_->growLightOff->time().msecsSinceStartOfDay();

    if (off < on)
        return;

    data_->setGrowLigtTime(on, off - on);
}

void FarmingWidget::onUpdateServerClicked(bool)
{
    data_->sendToServer();
}
