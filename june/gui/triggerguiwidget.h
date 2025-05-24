#ifndef TRIGGERGUIWIDGET_H
#define TRIGGERGUIWIDGET_H

#include <memory>

#include <QWidget>
#include <QTableView>

#include "triggerdatatablemodel.h"

#include "tabletool.h"

class TriggerData;
class QResizeEvent;
class TriggerTableModel;


namespace Ui {
class TriggerGuiWidget;
}

class TriggerGuiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TriggerGuiWidget(TriggerData *triggerData, QWidget *parent = nullptr);

private slots:
    void onCustomItemAddTriggerClicked(QString name);
private:
    TriggerData *triggerData = nullptr;

    std::unique_ptr<QTableView> tableView_;
    std::unique_ptr<TriggerDataTableModel> tableModel_;

    TableTool tableTool_;
    QString customItemAddTrigger_ = {"Add Trigger"};
};

#endif // TRIGGERGUIWIDGET_H
