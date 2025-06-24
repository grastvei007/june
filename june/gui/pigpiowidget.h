#ifndef PIGPIOWIDGET_H
#define PIGPIOWIDGET_H

#include <QWidget>
#include <memory>
#include <map>

#include "comboboxdelegate.h"

class PiGpioData;
class PiGpioTableModel;
class QTableView;

class PiGpioWidget : public QWidget
{
    Q_OBJECT
public:
    PiGpioWidget(PiGpioData *gpioData, QWidget *parent = nullptr);

private:
    void setupComboBoxData();
    PiGpioData *gpioData_ = nullptr;
    std::unique_ptr<PiGpioTableModel> tableModel_;
    std::unique_ptr<QTableView> tableView_;

    std::unique_ptr<ComboBoxDelegate> comboBoxDirectionDelegate_;
    std::unique_ptr<ComboBoxDelegate> enableDelegate_;

    std::map<QString, QVariant> comboboxData_;
    std::map<QString, QVariant> enableData_;
};

#endif // PIGPIOWIDGET_H
