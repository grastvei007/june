#ifndef TABLETOOL_H
#define TABLETOOL_H

#include <QObject>
#include <QTableView>
#include <QMenu>
#include <QDialog>
#include <vector>

class TableTool : public QObject
{
    Q_OBJECT
public:
    TableTool() : QObject() {}
    TableTool(QTableView *aTableView);


    TableTool& addRows(bool aValue);
    TableTool& removeRows(bool aValue);
    TableTool& addCustomItem(const QString &name);

    TableTool& build();

    TableTool& operator=(const TableTool &aTableTool);
signals:
    void customItemClicked(QString);
private slots:
    void onContextMenu(const QPoint &aPoint);
    void onAddRowClicked(bool);
    void onRemoveRowClicked(bool);
    void onCustomItemClicked(bool);

private:
    QTableView *mTableView = nullptr;
    QMenu *mContextMenu = nullptr;

    bool mAddRows = false;
    bool mRemoveRows = false;

    std::vector<QString> customItems_;
};

#endif // TABLETOOL_H
