#ifndef GARDENADATA_H
#define GARDENADATA_H

#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QObject>

class GardenaData : public QObject
{
	Q_OBJECT
  public:
	GardenaData(QNetworkAccessManager &nam,
				QNetworkRequestFactory &networkRequestFactory,
				QObject *parent = nullptr);

  private:
	QNetworkRequestFactory &networkRequestFactory_;
	QNetworkAccessManager &networkAccessManager_;
};

#endif // GARDENADATA_H
