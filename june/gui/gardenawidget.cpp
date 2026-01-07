#include "gardenawidget.h"
#include "ui_gardenawidget.h"

#include "data/gardenadata.h"

GardenaWidget::GardenaWidget(GardenaData *data, QWidget *parent)
	: QWidget(parent)
	, data_(data)
	, ui_(new Ui::GardenaWidget)
{
	ui_->setupUi(this);
}

GardenaWidget::~GardenaWidget()
{
	delete ui_;
}
