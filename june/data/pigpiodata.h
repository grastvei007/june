#ifndef PIGPIODATA_H
#define PIGPIODATA_H

#include <QObject>
#include <vector>

class QNetworkAccessManager;
class QNetworkRequestFactory;

class RpiGpioPin
{
public:
    RpiGpioPin(const QString &tagSubsystem,
               const QString &tagName,
               int wiringPiPin,
               const QString &direction,
               bool enabled);

    QString tagFullName() const;
    const QString &direction() const;
    int wiringPiPin() const;
    bool enabled() const;

    void setDirection(const QString &direction);
    void setEnabled(bool enabled);

private:
    QString tagSubsystem_;
    QString tagName_;
    int wiringPiPin_;
    QString direction_;
    bool enabled_;
};


class PiGpioData : public QObject
{
    Q_OBJECT
public:
    PiGpioData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    void fetchFromServer();
    int numberOfPins() const;

    const RpiGpioPin &getGpioPin(int index) const;

signals:
    void dataReady();

private slots:
    void onFetchFromServerFinnished();

private:
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;

    std::vector<RpiGpioPin> gpioPins_;
};

#endif // PIGPIODATA_H
