#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QString>

#include <map>
#include <memory>

#include <QComboBox>

class ComboBoxDelegate : public QStyledItemDelegate
{
    using itemText = QString;
    using itemValue = QVariant;
public:
    ComboBoxDelegate(const std::map<itemText, itemValue> &comboBoxData);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

private:
    std::map<itemText, itemValue> comboBoxData_;
    std::unique_ptr<QComboBox> comboBox_;
};

#endif // COMBOBOXDELEGATE_H
