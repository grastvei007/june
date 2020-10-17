#ifndef TRIGGERGUIWIDGET_H
#define TRIGGERGUIWIDGET_H

#include <QWidget>

class TriggerData;

namespace Ui {
class TriggerGuiWidget;
}

class TriggerGuiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TriggerGuiWidget(TriggerData *aTriggerData, QWidget *parent = nullptr);
    ~TriggerGuiWidget();

private:
    Ui::TriggerGuiWidget *ui;
};

#endif // TRIGGERGUIWIDGET_H
