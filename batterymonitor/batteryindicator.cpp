#include "batteryindicator.h"

#include <QRect>


BatteryIndicator::BatteryIndicator() :
    mIndicator(":/batteryLevel")
{
}


QImage BatteryIndicator::getBatteryState(State aState)
{
    QImage img;
    int width = mIndicator.width()/5;
    int height = mIndicator.height();
    switch (aState)
    {
        case eLevel1:
        {
            QRect rect(width*4, 0, width, height);
            img = mIndicator.copy(rect);
            break;
        }
        case eLevel2:
        {
            QRect rect(300, 0, width, height);
            img = mIndicator.copy(rect);
            break;
        }
        case eLevel3:
        {
            QRect rect(width*2, 0, width, height);
            img = mIndicator.copy(rect);
            break;
        }
        case eLevel4:
        {
            QRect rect(width*1, 0, width, height);
            img = mIndicator.copy(rect);
            break;
        }
        case eLevel5:
        {
            QRect rect(0, 0, width, height);
            img = mIndicator.copy(rect);
            break;
        }
    }


    return img;
}
