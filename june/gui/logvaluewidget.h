#ifndef LOGVALUEWIDGET_H
#define LOGVALUEWIDGET_H

#include <QWidget>
#include <memory>

#include "gui/tabletool.h"


class LogValueData;
class LogValueTableModel;
class QTableView;

class LogValueWidget : public QWidget
{
    Q_OBJECT
public:
    LogValueWidget(LogValueData *logValueData, QWidget *parent = nullptr);

private slots:
    void onCustomItemAddTriggerClicked(QString name);

private:
    LogValueData *logValueData_ = nullptr;
    TableTool tableTool_;

    std::unique_ptr<LogValueTableModel> tableModel_;
    std::unique_ptr<QTableView> tableView_;

    QString addValue_{"Add Value"};
    QString deleteItem_{"delete"};
};

#endif // LOGVALUEWIDGET_H
