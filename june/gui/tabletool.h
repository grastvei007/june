#ifndef TABLETOOL_H
#define TABLETOOL_H

#include <QObject>
#include <QTableView>
#include <QMenu>

class TableTool : public QObject
{
    Q_OBJECT
public:
    TableTool();
    TableTool(QTableView *aTableView);


    TableTool& addRows(bool aValue);
    TableTool& removeRows(bool aValue);

    TableTool& build();

    TableTool& operator=(const TableTool &aTableTool);
signals:

private slots:
    void onContextMenu(const QPoint &aPoint);
    void onAddRowClicked(bool);
    void onRemoveRowClicked(bool);

private:
    QTableView *mTableView = nullptr;
    QMenu *mContextMenu = nullptr;

    bool mAddRows = false;
    bool mRemoveRows = false;
};

#endif // TABLETOOL_H
