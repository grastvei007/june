#ifndef FARMINGWIDGET_H
#define FARMINGWIDGET_H

#include <QWidget>

class FarmingData;

namespace Ui {
class FarmingWidget;
}

class FarmingWidget : public QWidget
{
    Q_OBJECT
public:
    FarmingWidget(FarmingData *data, QWidget *parent = nullptr);

private:
    Ui::FarmingWidget *ui_;
    FarmingData *data_ = nullptr;
};

#endif // FARMINGWIDGET_H
