#include "systemtrayicon.h"

#include <QSystemTrayIcon>
#include <QIcon>
#include <QDebug>

#include <tagsystem/tagsocket.h>


SystemTrayIcon::SystemTrayIcon(QObject *parent) : QObject(parent),
    mBatteryIndicator(),
    mBatteryState(BatteryIndicator::eLevel1)
{
    mSystemTrayIcon.reset(new QSystemTrayIcon());
    QPixmap pmx = QPixmap::fromImage(mBatteryIndicator.getBatteryState(mBatteryState));
    mSystemTrayIcon->setIcon(QIcon(pmx));
    mSystemTrayIcon->setVisible(true);
    qDebug() << "set icon";

    mSocTagSocket.reset(TagSocket::createTagSocket("bm", "soc", TagSocket::eDouble));
    mSocTagSocket->hookupTag("BMV712_Smart", "SOC");
    connect(mSocTagSocket.get(), qOverload<double>(&TagSocket::valueChanged), this, &SystemTrayIcon::onStateOfChargeChange);
}

SystemTrayIcon::~SystemTrayIcon()
{

}


void SystemTrayIcon::onStateOfChargeChange(double aValue)
{
    qDebug() << aValue;
    double percent = aValue * 100;
    QString str = QString("%1 %").arg(percent);
    mSystemTrayIcon->setToolTip(str);

    BatteryIndicator::State currentState = BatteryIndicator::eLevel1;
    if(aValue > 90.0)
        currentState = BatteryIndicator::eLevel1;
    else if(aValue > 70.0)
        currentState = BatteryIndicator::eLevel2;
    else if(aValue > 50.0)
        currentState = BatteryIndicator::eLevel3;
    else if(aValue > 35.0)
        currentState = BatteryIndicator::eLevel4;
    else if(aValue > 25.0)
        currentState = BatteryIndicator::eLevel5;

    if(currentState != mBatteryState)
    {
        mBatteryState = currentState;
        QPixmap pmx = QPixmap::fromImage(mBatteryIndicator.getBatteryState(mBatteryState));
        mSystemTrayIcon->setIcon(QIcon(pmx));
        mSystemTrayIcon->setVisible(true);
    }
}
