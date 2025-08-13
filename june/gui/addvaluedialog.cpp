#include "addvaluedialog.h"
#include "ui_addvaluedialog.h"

#include <QLineEdit>
#include <QPushButton>

#include <tagsystem/tagselectview.h>
#include <tagsystem/tag.h>

AddValueDialog::AddValueDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddValueDialog)
{
    ui->setupUi(this);
    ui->tag->setReadOnly(true);

    connect(ui->selectButton, &QPushButton::clicked, this, &AddValueDialog::onSelectButtonClicked);
}

AddValueDialog::~AddValueDialog()
{
    delete ui;
}

QString AddValueDialog::tagbleName() const
{
    return ui->tableName->text();
}

QString AddValueDialog::valueName() const
{
    return ui->valueName->text();
}

QString AddValueDialog::tag() const
{
    return ui->tag->text();
}

void AddValueDialog::onSelectButtonClicked(bool)
{
    TagSelectView tagSelect(this);
    tagSelect.setAttribute(Qt::WA_QuitOnClose, false);
    if(tagSelect.exec())
    {
        auto *tag = tagSelect.getSelectedTag();
        if(tag)
        {
            ui->tag->clear();
            ui->tag->setText(tag->getFullName());
        }
    }
}
