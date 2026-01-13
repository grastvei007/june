#include "gardenawidget.h"
#include <QGridLayout>
#include <QHeaderView>

#include "data/gardenadata.h"
#include "gardenadatatablemodel.h"
#include "ui_gardenawidget.h"

#include <QPushButton>

GardenaWidget::GardenaWidget(GardenaData *data, QWidget *parent)
	: QWidget(parent)
	, data_(data)
	, ui_(new Ui::GardenaWidget)
{
	ui_->setupUi(this);

	tableModel_.reset(new GardenaDataTableModel(data_));

	tableView_.reset(new QTableView(this));
	tableView_->horizontalHeader()->setSectionsClickable(true);
	tableView_->horizontalHeader()->setStretchLastSection(true);
	tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableView_->setModel(tableModel_.get());

	QPushButton *button = new QPushButton("Update server");
	connect(button, &QPushButton::clicked, this, &GardenaWidget::onUpdateButtonClicked);

	QGridLayout *grid = new QGridLayout(this);
	grid->addWidget(tableView_.get());
	grid->addWidget(button);

	setLayout(grid);

	data_->fetchFromServer();
}

GardenaWidget::~GardenaWidget()
{
	delete ui_;
}

void GardenaWidget::onUpdateButtonClicked(bool)
{
	data_->sendToServer();
}
