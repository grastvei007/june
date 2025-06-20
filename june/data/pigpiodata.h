#ifndef PIGPIODATA_H
#define PIGPIODATA_H

#include <QObject>

class PiGpioData : public QObject
{
    Q_OBJECT
public:
    PiGpioData(QObject *parent = nullptr);
};

#endif // PIGPIODATA_H
