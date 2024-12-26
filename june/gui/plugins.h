#ifndef PLUGINS_H
#define PLUGINS_H

#include <QWidget>

class QNetworkAccessManager;

namespace Ui {
class Plugins;
}

class Plugins : public QWidget
{
    Q_OBJECT

public:
    explicit Plugins(QNetworkAccessManager& nam, QWidget *parent = nullptr);
    ~Plugins();

private:
    QNetworkAccessManager& networkAccessManager_;
    Ui::Plugins *ui;
};

#endif // PLUGINS_H
