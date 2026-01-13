#ifndef GARDENADATA_H
#define GARDENADATA_H

#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QObject>

#include "triggerbasedata.h"

class GardenaData : public TriggerBaseData
{
	Q_OBJECT
  public:
	GardenaData(QNetworkAccessManager &nam,
				QNetworkRequestFactory &networkRequestFactory,
				QObject *parent = nullptr);

  protected:
	void createMissingTriggers() override;

  private:
};

#endif // GARDENADATA_H
