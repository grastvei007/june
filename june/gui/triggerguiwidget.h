#ifndef TRIGGERGUIWIDGET_H
#define TRIGGERGUIWIDGET_H

#include <QWidget>
#include <QAbstractTableModel>

namespace Ui {
class TriggerGuiWidget;
}


class TriggerTableModel;


class TriggerGuiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TriggerGuiWidget(TriggerTableModel *triggerData, QWidget *parent = nullptr);
    ~TriggerGuiWidget();

private slots:
    void onAddTriggerClicked(bool);

private:
    Ui::TriggerGuiWidget *ui;
    TriggerTableModel *triggerTableModel_;
};

#endif // TRIGGERGUIWIDGET_H
