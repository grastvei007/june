#ifndef TAGSOCKETBINDINGWIDGET_H
#define TAGSOCKETBINDINGWIDGET_H

#include <QWidget>
#include <memory>

class TagSocketBindingData;
class TagSocketBindingTableModel;
class QTableView;

class TagSocketBindingWidget : public QWidget
{
public:
    TagSocketBindingWidget(TagSocketBindingData *data, QWidget *parent = nullptr);

private slots:
    void onDoubleClick(const QModelIndex &aIndex);

private:
    TagSocketBindingData *data_ = nullptr;

    std::unique_ptr<TagSocketBindingTableModel> tableModel_;
    std::unique_ptr<QTableView> tableView_;
};

#endif // TAGSOCKETBINDINGWIDGET_H
