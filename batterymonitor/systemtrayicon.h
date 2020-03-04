#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QObject>

#include <memory>

#include "batteryindicator.h"

class QSystemTrayIcon;
class TagSocket;

class SystemTrayIcon : public QObject
{
    Q_OBJECT
public:
    SystemTrayIcon(QObject *parent = nullptr);
    ~SystemTrayIcon();


signals:

private slots:
    void onStateOfChargeChange(double aValue);

private:
    std::unique_ptr<QSystemTrayIcon> mSystemTrayIcon;
    BatteryIndicator mBatteryIndicator;

    std::unique_ptr<TagSocket> mSocTagSocket;
    BatteryIndicator::State mBatteryState;
};

#endif // SYSTEMTRAYICON_H
