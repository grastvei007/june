#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <memory>

#include <QStatusBar>
#include <QLabel>

#include <tagsystem/tagsocket.h>

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

signals:

private slots:
    void onSystemTimeValueChanged(QDateTime aValue);

private:
    std::unique_ptr<TagSocket> mSystemTimeTagSocket;
    QLabel *mSystemTimeLabel;
};

#endif // STATUSBAR_H
