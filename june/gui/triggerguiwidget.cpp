#include "triggerguiwidget.h"
#include "ui_triggerguiwidget.h"

#include <QResizeEvent>

TriggerGuiWidget::TriggerGuiWidget(TriggerData *aTriggerData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriggerGuiWidget)
{
    ui->setupUi(this);

    mTableTool = TableTool(ui->tableView)
            .addRows(true)
            .removeRows(true)
            .build();

}

TriggerGuiWidget::~TriggerGuiWidget()
{
    delete ui;
}

