#ifndef PLUGINS_H
#define PLUGINS_H

#include <QWidget>

class QNetworkAccessManager;
class QNetworkRequestFactory;

namespace Ui {
class Plugins;
}

class Plugins : public QWidget
{
    Q_OBJECT

public:
    explicit Plugins(QNetworkAccessManager& nam, QNetworkRequestFactory& requestFactory, QWidget *parent = nullptr);
    ~Plugins();

private slots:
    void onLoadClicked(bool);
    void onUnloadClicked(bool);

private:
    QNetworkAccessManager& networkAccessManager_;
    QNetworkRequestFactory& networkRequestFactory_;
    Ui::Plugins *ui;
};

#endif // PLUGINS_H
