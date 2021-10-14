#include "triggerguiwidget.h"
#include "ui_triggerguiwidget.h"


TriggerGuiWidget::TriggerGuiWidget(QAbstractTableModel *triggerData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriggerGuiWidget)
{
    ui->setupUi(this);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(triggerData);
}

TriggerGuiWidget::~TriggerGuiWidget()
{
    delete ui;
}
