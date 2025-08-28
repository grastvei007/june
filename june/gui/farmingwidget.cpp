#include "farmingwidget.h"

#include "ui_farmingwidget.h"

#include "data/farmingdata.h"

FarmingWidget::FarmingWidget(FarmingData *data, QWidget *parent) :
    QWidget(parent),
    data_(data),
    ui_(new Ui::FarmingWidget)
{
    ui_->setupUi(this);

}
