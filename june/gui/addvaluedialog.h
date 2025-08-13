#ifndef ADDVALUEDIALOG_H
#define ADDVALUEDIALOG_H

#include <QDialog>

namespace Ui {
class AddValueDialog;
}

class AddValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddValueDialog(QWidget *parent = nullptr);
    ~AddValueDialog();

    QString tagbleName() const;
    QString valueName() const;
    QString tag() const;
private slots:
    void onSelectButtonClicked(bool);

private:
    Ui::AddValueDialog *ui;
};

#endif // ADDVALUEDIALOG_H
