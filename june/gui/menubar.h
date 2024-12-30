#ifndef MENUBAR_H
#define MENUBAR_H

#include <memory>

#include <QMenuBar>

class QMenu;
class QWidgets;
class QNetworkAccessManager;
class Plugins;
class QNetworkRequestFactory;

class MenuBar : public QMenuBar
{
public:
   MenuBar(QNetworkAccessManager &nam, QNetworkRequestFactory& requestFactory);

private slots:
   void onTagListClicked(bool);
   void onTagSocketListClicked(bool);
   void onConnectToServerClicked(bool);
   void onDisconnectFromServerClicked(bool);

   void onServerPluginClicked(bool);

private:
   QNetworkAccessManager& networkAccessManager_;
   QNetworkRequestFactory& networkRequestFactory_;

   std::unique_ptr<QMenu> fileMenu_;
   std::unique_ptr<QMenu> mViewMenu;
   std::unique_ptr<QMenu> serverMenu_;

   std::unique_ptr<QAction> connectToServerAction_;
   std::unique_ptr<QAction> disconnectFromServerAction_;

   std::unique_ptr<QWidget> mTagListViewWidget;
   std::unique_ptr<QWidget> mTagSocketListViewWidget;

   std::unique_ptr<Plugins> serverPluginWidget_;
};

#endif // MENUBAR_H
