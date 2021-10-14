#include "triggerguiwidget.h"
#include "ui_triggerguiwidget.h"

#include "addtriggerdialog.h"
#include "../triggermanager/triggertablemodel.h"


TriggerGuiWidget::TriggerGuiWidget(TriggerTableModel *triggerData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TriggerGuiWidget),
    triggerTableModel_(triggerData)
{
    ui->setupUi(this);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(triggerData);

    connect(ui->addTriger, &QPushButton::clicked, this, &TriggerGuiWidget::onAddTriggerClicked);
}

TriggerGuiWidget::~TriggerGuiWidget()
{
    delete ui;
}

void TriggerGuiWidget::onAddTriggerClicked(bool)
{
    AddTriggerDialog addTriggerDialog(triggerTableModel_);
    if(addTriggerDialog.exec() == QDialog::Accepted)
        addTriggerDialog.createTrigger();
}
