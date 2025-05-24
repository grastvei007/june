#include "gui/tabletool.h"


TableTool::TableTool(QTableView *aTableView) : QObject(),
    mTableView(aTableView)
{

}

TableTool &TableTool::addRows(bool aValue)
{
    mAddRows = aValue;
    return *this;
}

TableTool &TableTool::removeRows(bool aValue)
{
    mRemoveRows = aValue;
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

TableTool &TableTool::operator=(const TableTool &aTableTool)
{
    mTableView = aTableTool.mTableView;
    mAddRows = aTableTool.mAddRows;
    mRemoveRows = aTableTool.mRemoveRows;

    if(mAddRows || mRemoveRows || !customItems_.empty())
    {
        if(!mContextMenu)
            mContextMenu = new QMenu();
    }

    if(mAddRows)
    {
        QAction *add = mContextMenu->addAction("Add Row");
        connect(add, &QAction::triggered, this, &TableTool::onAddRowClicked);
    }

    if(mRemoveRows)
    {
        QAction *remove = mContextMenu->addAction("Remove Row");
        connect(remove, &QAction::triggered, this, &TableTool::onRemoveRowClicked);
    }

    for(const auto& item : customItems_)
    {
        QAction *customItem = mContextMenu->addAction(item);
        connect(customItem, &QAction::triggered, this, &TableTool::onCustomItemClicked);
    }

    if(mContextMenu)
    {
        mTableView->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(mTableView, &QTableView::customContextMenuRequested, this, &TableTool::onContextMenu);
    }

    return *this;
}

void TableTool::onContextMenu(const QPoint &aPoint)
{
    mContextMenu->popup(mTableView->viewport()->mapToGlobal(aPoint));
}

void TableTool::onAddRowClicked(bool aTriggered)
{
    Q_UNUSED(aTriggered);
    if(!mTableView->model())
        return;

    int rows = mTableView->model()->rowCount();
    mTableView->model()->insertRow(rows+1);
}

void TableTool::onRemoveRowClicked(bool aTriggered)
{
    Q_UNUSED(aTriggered);
}

void TableTool::onCustomItemClicked(bool triggered)
{
    Q_UNUSED(triggered);
    QAction *caller = qobject_cast<QAction*>(sender());
    auto text =caller->text();
    emit customItemClicked(text);
}
