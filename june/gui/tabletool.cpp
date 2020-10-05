#include "tabletool.h"

TableTool::TableTool()
{

}

TableTool::TableTool(QTableView *aTableView) :
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

TableTool& TableTool::build()
{

    return *this;
}

TableTool &TableTool::operator=(const TableTool &aTableTool)
{
    mTableView = aTableTool.mTableView;
    mAddRows = aTableTool.mAddRows;
    mRemoveRows = aTableTool.mRemoveRows;

    if(mAddRows)
    {
        if(!mContextMenu)
            mContextMenu = new QMenu();

        QAction *add = mContextMenu->addAction("Add Row");
        connect(add, &QAction::triggered, this, &TableTool::onAddRowClicked);
    }

    if(mRemoveRows)
    {
        if(!mContextMenu)
            mContextMenu = new QMenu();

        QAction *remove = mContextMenu->addAction("Remove Row");
        connect(remove, &QAction::triggered, this, &TableTool::onRemoveRowClicked);
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
