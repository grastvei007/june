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

    gpioData_->fetchFromServer();
}
