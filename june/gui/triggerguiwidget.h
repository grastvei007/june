#ifndef TRIGGERGUIWIDGET_H
#define TRIGGERGUIWIDGET_H

#include <QWidget>

#include "tabletool.h"

class TriggerData;
class QResizeEvent;


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
    TableTool mTableTool;
};

#endif // TRIGGERGUIWIDGET_H
