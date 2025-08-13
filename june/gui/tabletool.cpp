#include "gui/tabletool.h"

#include <QItemSelectionModel>


TableTool::TableTool(QTableView *tableView) : QObject(),
    tableView_(tableView)
{

}

TableTool &TableTool::addRows(bool value)
{
    addRows_ = value;
    return *this;
}

TableTool &TableTool::removeRows(bool value)
{
    removeRows_ = value;
    return *this;
}

TableTool &TableTool::addCustomItem(const QString &name)
{
    customItems_.push_back(name);
    return *this;
}

TableTool& TableTool::build()
{

    return *this;
}

TableTool &TableTool::operator=(const TableTool &tableTool)
{
    tableView_ = tableTool.tableView_;
    addRows_ = tableTool.addRows_;
    removeRows_ = tableTool.removeRows_;
    customItems_ = tableTool.customItems_;

    if(addRows_ || removeRows_ || !customItems_.empty())
    {
        if(!contextMenu_)
            contextMenu_ = new QMenu();
    }

    if(addRows_)
    {
        QAction *add = contextMenu_->addAction("Add Row");
        connect(add, &QAction::triggered, this, &TableTool::onAddRowClicked);
    }

    if(removeRows_)
    {
        QAction *remove = contextMenu_->addAction("Remove Row");
        connect(remove, &QAction::triggered, this, &TableTool::onRemoveRowClicked);
    }

    for(const auto& item : customItems_)
    {
        QAction *customItem = contextMenu_->addAction(item);
        connect(customItem, &QAction::triggered, this, &TableTool::onCustomItemClicked);
    }

    if(contextMenu_)
    {
        tableView_->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(tableView_, &QTableView::customContextMenuRequested, this, &TableTool::onContextMenu);
    }

    return *this;
}

void TableTool::onContextMenu(const QPoint &point)
{
    contextMenu_->popup(tableView_->viewport()->mapToGlobal(point));
}

void TableTool::onAddRowClicked(bool triggered)
{
    Q_UNUSED(triggered);
    if(!tableView_->model())
        return;

    int rows = tableView_->model()->rowCount();
    tableView_->model()->insertRow(rows+1);
}

void TableTool::onRemoveRowClicked(bool triggered)
{
    Q_UNUSED(triggered);
    QModelIndex index  = tableView_->currentIndex();
    if(index.isValid())
        tableView_->model()->removeRows(index.row(), 1, index);
}

void TableTool::onCustomItemClicked(bool triggered)
{
    Q_UNUSED(triggered);
    QAction *caller = qobject_cast<QAction*>(sender());
    auto text =caller->text();
    emit customItemClicked(text);
}
