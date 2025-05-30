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
    TableTool(QTableView *tableView);


    TableTool& addRows(bool value);
    TableTool& removeRows(bool value);
    TableTool& addCustomItem(const QString &name);

    TableTool& build();

    TableTool& operator=(const TableTool &tableTool);
signals:
    void customItemClicked(QString);
private slots:
    void onContextMenu(const QPoint &point);
    void onAddRowClicked(bool);
    void onRemoveRowClicked(bool);
    void onCustomItemClicked(bool);

private:
    QTableView *tableView_ = nullptr;
    QMenu *contextMenu_ = nullptr;

    bool addRows_ = false;
    bool removeRows_ = false;

    std::vector<QString> customItems_;
};

#endif // TABLETOOL_H
