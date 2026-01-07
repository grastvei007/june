#ifndef GARDENAWIDGET_H
#define GARDENAWIDGET_H

#include <QWidget>

class GardenaData;

namespace Ui {

class GardenaWidget;

}

class GardenaWidget : public QWidget
{
	Q_OBJECT

  public:
	explicit GardenaWidget(GardenaData *data, QWidget *parent = nullptr);
	~GardenaWidget();

  private:
	Ui::GardenaWidget *ui_;
	GardenaData *data_ = nullptr;
};

#endif // GARDENAWIDGET_H
