#include "pigpiowidget.h"

#include "../data/pigpiodata.h"

PiGpioWidget::PiGpioWidget(PiGpioData *gpioData, QWidget *parent) : QWidget(parent),
    gpioData_(gpioData)
{

}
