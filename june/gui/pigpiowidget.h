#ifndef PIGPIOWIDGET_H
#define PIGPIOWIDGET_H

#include <QWidget>

class PiGpioData;

class PiGpioWidget : public QWidget
{
    Q_OBJECT
public:
    PiGpioWidget(PiGpioData *gpioData, QWidget *parent = nullptr);

private:
    PiGpioData *gpioData_ = nullptr;
};

#endif // PIGPIOWIDGET_H
