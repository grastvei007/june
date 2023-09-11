#include "triggerguiwidget.h"

#include <QHeaderView>
#include <QGridLayout>


TriggerGuiWidget::TriggerGuiWidget(TriggerData *triggerData, QWidget *parent) :
    QWidget(parent)
{
    tableModel_.reset(new TriggerDataTableModel(triggerData));

    tableView_.reset(new QTableView(this));
    tableView_->horizontalHeader()->setSectionsClickable(true);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->setModel(tableModel_.get());

    tableTool_ = TableTool(tableView_.get())
                     .addRows(true)
                     .removeRows(true)
                     .build();

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(tableView_.get());

    setLayout(grid);
}

