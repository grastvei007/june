#ifndef TRIGGERBASEDATA_H
#define TRIGGERBASEDATA_H

#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QObject>
#include <QString>
#include <vector>

#include "trigger.h"

class TriggerBaseData : public QObject
{
	Q_OBJECT
  public:
	explicit TriggerBaseData(QNetworkAccessManager &nam,
							 QNetworkRequestFactory &networkRequestFactory,
							 QObject *parent = nullptr);

	QJsonArray createRequestArray(const std::vector<QString> &list) const;

	void fetchFromServer();
	void sendToServer();

  signals:
	void dataReady();

  private slots:
	void onFetchFromServerFinnished();

  protected:
	virtual void createMissingTriggers() = 0;

	QNetworkRequestFactory &networkRequestFactory_;
	QNetworkAccessManager &networkAccessManager_;

	std::vector<QString> requestedTriggers_;
	std::vector<Trigger> triggers_;

	bool triggersExistOnServer_ = false;
};

#endif // TRIGGERBASEDATA_H
