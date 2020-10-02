#include "triggerguiwidget.h"
#include "ui_triggerguiwidget.h"

TriggerGuiWidget::TriggerGuiWidget(TriggerData *aTriggerData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriggerGuiWidget)
{
    ui->setupUi(this);
}

TriggerGuiWidget::~TriggerGuiWidget()
{
    delete ui;
}
