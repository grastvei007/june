#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H

#include <QObject>
#include <QImage>


class BatteryIndicator
{
public:
    enum State
    {
        eLevel1,
        eLevel2,
        eLevel3,
        eLevel4,
        eLevel5
    };
    BatteryIndicator();

    QImage getBatteryState(State aState);

private:
    QImage mIndicator;
};

#endif // BATTERYINDICATOR_H
