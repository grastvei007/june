#include "logvaluewidget.h"

#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>

#include "gui/logvaluetablemodel.h"
#include "gui/addvaluedialog.h"
#include "data/logvaluedata.h"


LogValueWidget::LogValueWidget(LogValueData *logValueData, QWidget *parent) :
    QWidget(parent),
    logValueData_(logValueData)
{
    tableModel_ = std::make_unique<LogValueTableModel>(logValueData);

    tableView_ = std::make_unique<QTableView>(this);
    tableView_->horizontalHeader()->setSectionsClickable(true);
    tableView_->horizontalHeader()->setStretchLastSection(true);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_->setModel(tableModel_.get());

    tableTool_ = TableTool(tableView_.get())
                     .addCustomItem(addValue_)
                     .removeRows(true)
                     .build();
    connect(&tableTool_, &TableTool::customItemClicked, this, &LogValueWidget::onCustomItemAddTriggerClicked);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(tableView_.get());

    setLayout(grid);

    logValueData_->fetchFromServer();
}

void LogValueWidget::onCustomItemAddTriggerClicked(QString name)
{
    if(name == addValue_)
    {
        AddValueDialog dialog;
        if(dialog.exec() == QDialog::Accepted)
        {
            auto tableName = dialog.tagbleName();
            auto valueName = dialog.valueName();
            auto tag = dialog.tag();
            if(!tableName.isEmpty() && !valueName.isEmpty() && !tag.isEmpty())
            {
                logValueData_->addLogValue(tableName, valueName, tag);
            }
        }
    }
}
