#include "addtrigger.h"
#include "ui_addtrigger.h"
#include <QString>

AddTrigger::AddTrigger(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTrigger)
{
    ui->setupUi(this);
    setWindowTitle("Add Trigger");
}

AddTrigger::~AddTrigger()
{
    delete ui;
}

void AddTrigger::populateComboTypes(QStringList list)
{
    ui->cbType->addItems(list);
}

QString AddTrigger::triggerName() const
{
    return ui->triggerName->text();
}

QString AddTrigger::triggerType() const
{
    return ui->cbType->currentText();
}

QString AddTrigger::watchTag() const
{
    return ui->watchTag->text();
}

double AddTrigger::targetValue() const
{
    return ui->targetValue->text().toDouble();
}

int AddTrigger::targetValueSec() const
{
    return ui->targetValue->text().toInt();
}

int AddTrigger::duration() const
{
    return ui->duration->text().toInt();
}
