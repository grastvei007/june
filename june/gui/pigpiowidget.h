#ifndef PIGPIOWIDGET_H
#define PIGPIOWIDGET_H

#include <QWidget>
#include <memory>

class PiGpioData;
class PiGpioTableModel;
class QTableView;

class PiGpioWidget : public QWidget
{
    Q_OBJECT
public:
    PiGpioWidget(PiGpioData *gpioData, QWidget *parent = nullptr);

private:
    PiGpioData *gpioData_ = nullptr;
    std::unique_ptr<PiGpioTableModel> tableModel_;
    std::unique_ptr<QTableView> tableView_;
};

#endif // PIGPIOWIDGET_H
