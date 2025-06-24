#include "pigpiowidget.h"

#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>

#include "../data/pigpiodata.h"

#include "pigpiotablemodel.h"


PiGpioWidget::PiGpioWidget(PiGpioData *gpioData, QWidget *parent)
    : QWidget(parent)
    , gpioData_(gpioData)
{
    tableModel_.reset(new PiGpioTableModel(gpioData_));

    tableView_.reset(new QTableView(this));
    tableView_->horizontalHeader()->setSectionsClickable(true);
    tableView_->horizontalHeader()->setStretchLastSection(true);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->setModel(tableModel_.get());

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(tableView_.get());

    setLayout(grid);

    setupComboBoxData();
    comboBoxDirectionDelegate_.reset(new ComboBoxDelegate(comboboxData_));
    enableDelegate_.reset(new ComboBoxDelegate(enableData_));
    tableView_->setItemDelegateForColumn(PiGpioTableModel::eDirection,
                                         comboBoxDirectionDelegate_.get());
    tableView_->setItemDelegateForColumn(PiGpioTableModel::eEnabled, enableDelegate_.get());

    gpioData_->fetchFromServer();
}

void PiGpioWidget::setupComboBoxData()
{
    comboboxData_.insert(std::pair("in", "in"));
    comboboxData_.insert(std::pair("out", "out"));
    comboboxData_.insert(std::pair("pwm", "pwm"));

    enableData_.insert(std::pair("enable", true));
    enableData_.insert(std::pair("disable", false));
}
