#include "addtriggerdialog.h"
#include "ui_addtriggerdialog.h"

#include <QDebug>

#include "../triggermanager/triggertablemodel.h"
#include "../triggermanager/triggers/valuetrigger.h"

#include <tagsystem/tagselectview.h>
#include <tagsystem/tag.h>

AddTriggerDialog::AddTriggerDialog(TriggerTableModel *triggerTableModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTriggerDialog),
    triggerTableModel_(triggerTableModel)
{
    ui->setupUi(this);
    ui->triggerType->addItems( triggerTableModel_->triggerTypes() );
    ui->triggerCombo->addItems(triggerTableModel_->trigger());

    connect(ui->selectTagPushButton, &QPushButton::clicked, this, &AddTriggerDialog::onSelectTagClicked);
    connect(ui->triggerCombo, &QComboBox::currentTextChanged, this, &AddTriggerDialog::onTriggerTexetChanged);
    connect(ui->triggerType, &QComboBox::currentTextChanged, this, &AddTriggerDialog::onTriggerTypeTextChanged);

    onTriggerTypeTextChanged(ui->triggerType->currentText());
    onTriggerTexetChanged(ui->triggerCombo->currentText());
}

AddTriggerDialog::~AddTriggerDialog()
{
    delete ui;
}

void AddTriggerDialog::createTrigger()
{
    QString name = ui->triggerName->text();
    QString tagName = ui->selectedTag->text();
    double triggerValue = ui->triggerValue->text().toDouble();
    TriggerFunction::Values trigger = TriggerFunction::fromString(ui->triggerCombo->currentText());
    ValueTrigger *valueTrigger = new ValueTrigger(name, tagName, trigger, triggerValue);

}

void AddTriggerDialog::onSelectTagClicked(bool)
{
    TagSelectView tagSelectView(this);
    tagSelectView.setVisible(true);
    if(tagSelectView.exec() == QDialog::Accepted)
    {
        auto selectedTag = tagSelectView.getSelectedTag();
        if(selectedTag)
        {
            ui->selectedTag->clear();
            ui->selectedTag->setText(selectedTag->getFullName());
        }
    }
}

void AddTriggerDialog::onTriggerTypeTextChanged(QString text)
{
    triggerType_ = Trigger::triggerTypeFromString(text);
}

void AddTriggerDialog::onTriggerTexetChanged(QString text)
{
    qDebug() << text;
}
