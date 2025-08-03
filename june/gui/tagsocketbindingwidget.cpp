#include "tagsocketbindingwidget.h"

#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>

#include <tagsystem/tagselectview.h>

#include "tagsocketbindingtablemodel.h"
#include "data/tagsocketbindingdata.h"

TagSocketBindingWidget::TagSocketBindingWidget(TagSocketBindingData *data, QWidget *parent)
    : QWidget(parent),
    data_(data)
{
    tableModel_.reset(new TagSocketBindingTableModel(data_));
    tableView_.reset(new QTableView(this));

    connect(tableView_.get(), &QTableView::doubleClicked, this, &TagSocketBindingWidget::onDoubleClick);

    tableView_->horizontalHeader()->setSectionsClickable(true);
    tableView_->horizontalHeader()->setStretchLastSection(true);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->setModel(tableModel_.get());

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(tableView_.get());

    setLayout(grid);

    data_->fetchFromServer();
}

void TagSocketBindingWidget::onDoubleClick(const QModelIndex &index)
{
    if(index.column() != TagSocketBindingTableModel::eTag)
        return;

    auto idx = tableModel_->index(index.row(), TagSocketBindingTableModel::eType);

    auto type = TagSocket::typeFromString(idx.data().toString());

    TagSelectView tagSelect;
    tagSelect.setAttribute(Qt::WA_QuitOnClose, false);
    tagSelect.setFilterTagTypeCompatibleWithTagSocketType(type);

    if(tagSelect.exec() == QDialog::Accepted)
    {
        Tag *tag = tagSelect.getSelectedTag();
        if(tag)
            tableView_->model()->setData(index, tag->getFullName(), Qt::EditRole);
    }
}
