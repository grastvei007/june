#ifndef LOGVALUEDATA_H
#define LOGVALUEDATA_H

#include <QObject>
#include <vector>

class QNetworkAccessManager;
class QNetworkRequestFactory;

class LogValue
{
public:
    LogValue(const QString& tagSocketSubsystem, const QString& tagSocketName, const QString& tagSubsystem, const QString& tagName);

    QString tagSocketFullName() const;
    const QString& tagSocketSubsystem() const;
    const QString& tagSocketName() const;
    QString tag() const;
private:
    QString tagSocketSubsystem_;
    QString tagSocketName_;
    QString tagSubsystem_;
    QString tagName_;
};


class LogValueData : public QObject
{
    Q_OBJECT
public:
    LogValueData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    const LogValue& value(int index) const;
    int numberOfValue() const;
    void fetchFromServer();

    void deleteLogValue(int index);
    void addLogValue(const QString& tagsocketSubsystem, const QString& tagsocketName, const QString& tag);

signals:
    void dataReady();
    void logValueDeleted(int index);
    void logValueAdded();

private slots:
    void onFetchFromServerFinnished();
    void onDeleteFinnished();
    void onAddFinnished();

private:
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;

    std::vector<LogValue> logValues_;
};

#endif // LOGVALUEDATA_H
