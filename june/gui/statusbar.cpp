#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent) : QStatusBar(parent)
{
    mSystemTimeTagSocket.reset(TagSocket::createTagSocket("system", "time", TagSocket::eTime));
    mSystemTimeTagSocket->hookupTag("system", "time");
    connect(mSystemTimeTagSocket.get(), qOverload<QDateTime>(&TagSocket::valueChanged), this, &StatusBar::onSystemTimeValueChanged);

    mSystemTimeLabel = new QLabel(this);
    addPermanentWidget(mSystemTimeLabel);
}

void StatusBar::onSystemTimeValueChanged(QDateTime aValue)
{
    clearMessage();
    showMessage(aValue.toString());
}
