#include "triggerguiwidget.h"

#include <QHeaderView>
#include <QGridLayout>
#include <QComboBox>
#include <QFileDialog>

#include "addtrigger.h"
#include "../data/triggerdata.h"

TriggerGuiWidget::TriggerGuiWidget(TriggerData *triggerData, QWidget *parent) :
    triggerData_(triggerData),
    QWidget(parent)
{
    tableModel_.reset(new TriggerDataTableModel(triggerData));

    tableView_.reset(new QTableView(this));
    tableView_->horizontalHeader()->setSectionsClickable(true);
    tableView_->horizontalHeader()->setStretchLastSection(true);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->setModel(tableModel_.get());

    tableTool_ = TableTool(tableView_.get())
                     .removeRows(true)
                     .addCustomItem(customItemAddTrigger_)
                     .addCustomItem(customItemUploadFromFile_)
                     .build();

    connect(&tableTool_, &TableTool::customItemClicked, this, &TriggerGuiWidget::onCustomItemAddTriggerClicked);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(tableView_.get());

    setLayout(grid);

    triggerData_->fetchFromServer();
}

void TriggerGuiWidget::onCustomItemAddTriggerClicked(QString name)
{
    if (name == customItemAddTrigger_)
    {
        AddTrigger addTrigger;
        addTrigger.populateComboTypes(triggerData_->triggerTypes());
        if (addTrigger.exec() == QDialog::Accepted)
        {
            auto type = triggerData_->fromString(addTrigger.triggerType()).value();
            auto triggerName = addTrigger.triggerName();
            auto watchTag = addTrigger.watchTag();
            if (type == TriggerType::TriggerEveryTimeAbove
                || type == TriggerType::TriggerEveryTimeBelow)
            {
                double value = addTrigger.targetValue();
                triggerData_->createTrigger(type, triggerName, watchTag, value);
                return;
            } else if (type == TriggerType::TriggerOnTime)
            {
                int value = addTrigger.targetValueSec();
                auto duration = addTrigger.duration();
                triggerData_->createTrigger(type, triggerName, watchTag, value, duration);
                return;
            }
        }
    } else if (name == customItemUploadFromFile_)
    {
        auto fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open Triggers"),
                                                     QDir::homePath(),
                                                     tr("Trigger Files (*.json)"));
        if (!fileName.isEmpty())
        {
            triggerData_->uplaodTriggerFile(fileName);
        }
    }
}
