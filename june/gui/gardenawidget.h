#ifndef GARDENAWIDGET_H
#define GARDENAWIDGET_H

#include <QTableView>
#include <QWidget>
#include <memory>

class GardenaData;
class GardenaDataTableModel;

namespace Ui {

class GardenaWidget;

}

class GardenaWidget : public QWidget
{
	Q_OBJECT

  public:
	explicit GardenaWidget(GardenaData *data, QWidget *parent = nullptr);
	~GardenaWidget();

  private slots:
	void onUpdateButtonClicked(bool);

  private:
	Ui::GardenaWidget *ui_;
	GardenaData *data_ = nullptr;

	std::unique_ptr<QTableView> tableView_;
	std::unique_ptr<GardenaDataTableModel> tableModel_;
};

#endif // GARDENAWIDGET_H
