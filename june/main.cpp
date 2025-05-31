#include "mainwindow.h"
#include "app.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

QtMessageHandler defaultHandler {};
QFile logFile;


void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString & msg)
{
    QString text;
    QString timestamp = QDateTime::currentDateTime().toString();
    switch (type)
    {
    case QtInfoMsg:
        text = QString("Info [%1]: %2").arg(timestamp, msg);
        break;
    case QtDebugMsg:
        text = QString("Debug [%1]: %2").arg(timestamp, msg);
        break;
    case QtWarningMsg:
        text = QString("Warning [%1]: %2").arg(timestamp, msg);
        break;
    case QtCriticalMsg:
        text = QString("Critical [%1]: %2").arg(timestamp, msg);
        break;
    case QtFatalMsg:
        text = QString("Fatal [%1]: %2").arg(timestamp, msg);
        break;
    }

    QTextStream stream(&logFile);
    stream << text << "\n";

    defaultHandler(type, context, text);

    if(type == QtFatalMsg)
    {
        logFile.close();
        abort();
    }
}

int main(int argc, char *argv[])
{
    defaultHandler = qInstallMessageHandler(myMessageHandler);
    logFile.setFileName("juneserver.log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

    App app(argc, argv);
    return app.exec();
}
