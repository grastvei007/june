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
    explicit TriggerGuiWidget(QAbstractTableModel *triggerData, QWidget *parent = nullptr);
    ~TriggerGuiWidget();

private:
    Ui::TriggerGuiWidget *ui;
};

#endif // TRIGGERGUIWIDGET_H
