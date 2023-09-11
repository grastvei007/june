#ifndef TRIGGERGUIWIDGET_H
#define TRIGGERGUIWIDGET_H

#include <memory>

#include <QWidget>
#include <QTableView>

#include "triggerdatatablemodel.h"

class TriggerData;

namespace Ui {
class TriggerGuiWidget;
}

class TriggerGuiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TriggerGuiWidget(TriggerData *triggerData, QWidget *parent = nullptr);

private:
    TriggerData *triggerData = nullptr;

    std::unique_ptr<QTableView> tableView_;
    std::unique_ptr<TriggerDataTableModel> tableModel_;
};

#endif // TRIGGERGUIWIDGET_H
