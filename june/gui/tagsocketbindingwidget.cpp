#include "tagsocketbindingwidget.h"

#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>

#include "tagsocketbindingtablemodel.h"
#include "data/tagsocketbindingdata.h"

TagSocketBindingWidget::TagSocketBindingWidget(TagSocketBindingData *data, QWidget *parent)
    : QWidget(parent),
    data_(data)
{
    tableModel_.reset(new TagSocketBindingTableModel(data_));
    tableView_.reset(new QTableView(this));

    tableView_->horizontalHeader()->setSectionsClickable(true);
    tableView_->horizontalHeader()->setStretchLastSection(true);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->setModel(tableModel_.get());

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(tableView_.get());

    setLayout(grid);

    data_->fetchFromServer();
}
