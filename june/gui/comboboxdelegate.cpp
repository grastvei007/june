#include "comboboxdelegate.h"

#include <QStyleOptionViewItem>

ComboBoxDelegate::ComboBoxDelegate(const std::map<itemText, itemValue> &comboBoxData)
    : comboBoxData_(comboBoxData)
{}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    QComboBox *combo = new QComboBox(parent);
    for (const auto &[text, value] : comboBoxData_)
    {
        combo->addItem(text, value);
    }
    return combo;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto *comboBox = qobject_cast<QComboBox *>(editor);
    auto data = index.data();
    auto currentValue = std::ranges::find_if(comboBoxData_, [&data](const auto &elm) {
        return elm.second == data;
    });
    if (currentValue != comboBoxData_.end())
    {
        auto text = comboBoxData_.at(currentValue->first);
        comboBox->setCurrentText(text.toString());
    }
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    auto *comboBox = qobject_cast<QComboBox *>(editor);
    auto text = comboBox->currentText();
    model->setData(index, comboBoxData_.at(text));
}
