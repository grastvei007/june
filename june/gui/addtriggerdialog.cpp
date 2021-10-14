#include "addtriggerdialog.h"
#include "ui_addtriggerdialog.h"

#include "../triggermanager/triggertablemodel.h"

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
}

AddTriggerDialog::~AddTriggerDialog()
{
    delete ui;
}

void AddTriggerDialog::createTrigger()
{

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
