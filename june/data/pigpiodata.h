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
			   const QString &hookupTag,
               const QString &tagName,
               int wiringPiPin,
               const QString &direction,
               bool enabled);

    QString tagFullName() const;
	QString hookupTag() const;
    const QString &direction() const;
    int wiringPiPin() const;
    bool enabled() const;

    void setDirection(const QString &direction);
    void setEnabled(bool enabled);

private:
    QString tagSubsystem_;
	QString hookupTag_;
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
    void updatePinDirection(int index, QString direction);
    void updatePinEnable(int index, bool enabled);

signals:
    void dataReady();
    void directionUpdated();
    void enabledUpdated();

private slots:
    void onFetchFromServerFinnished();
    void onUpdateResponseFromServer();

private:
    void updateConfig(const QJsonObject &obj);
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;

    std::vector<RpiGpioPin> gpioPins_;
};

#endif // PIGPIODATA_H
