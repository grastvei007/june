#ifndef MENUBAR_H
#define MENUBAR_H

#include <memory>

#include <QMenuBar>

class QMenu;
class QWidgets;

class MenuBar : public QMenuBar
{
public:
   MenuBar();

private slots:
   void onTagListClicked(bool);
   void onTagSocketListClicked(bool);
   void onConnectToServerClicked(bool);
   void onDisconnectFromServerClicked(bool);

private:
   std::unique_ptr<QMenu> fileMenu_;
   std::unique_ptr<QMenu> mViewMenu;

   std::unique_ptr<QAction> connectToServerAction_;
   std::unique_ptr<QAction> disconnectFromServerAction_;

   std::unique_ptr<QWidget> mTagListViewWidget;
   std::unique_ptr<QWidget> mTagSocketListViewWidget;
};

#endif // MENUBAR_H
