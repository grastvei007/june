#ifndef ADDTRIGGER_H
#define ADDTRIGGER_H

#include <QDialog>

namespace Ui {
class AddTrigger;
}

class AddTrigger : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrigger(QWidget *parent = nullptr);
    ~AddTrigger();

    void populateComboTypes(QStringList list);

    QString triggerName() const;
    QString triggerType() const;
    QString watchTag() const;
    double targetValue() const;
    int targetValueSec() const;
    int duration() const;


private:
    Ui::AddTrigger *ui;
};

#endif // ADDTRIGGER_H
