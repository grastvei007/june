#ifndef ADDTRIGGERDIALOG_H
#define ADDTRIGGERDIALOG_H

#include <QDialog>
#include <QStringList>

#include "../triggermanager/trigger.h"

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
    void onTriggerTypeTextChanged(QString text);
    void onTriggerTexetChanged(QString text);

private:
    Ui::AddTriggerDialog *ui;

    TriggerTableModel *triggerTableModel_;

    TriggerType triggerType_ = TriggerType::eNone;
};

#endif // ADDTRIGGERDIALOG_H
