#ifndef ADDTRIGGERDIALOG_H
#define ADDTRIGGERDIALOG_H

#include <QDialog>
#include <QStringList>

class TriggerTableModel;

namespace Ui {
class AddTriggerDialog;
}

class AddTriggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTriggerDialog(TriggerTableModel *triggerTableModel, QWidget *parent = nullptr);
    ~AddTriggerDialog();

    void createTrigger();

private slots:
    void onSelectTagClicked(bool);

private:
    Ui::AddTriggerDialog *ui;

    TriggerTableModel *triggerTableModel_;
};

#endif // ADDTRIGGERDIALOG_H
