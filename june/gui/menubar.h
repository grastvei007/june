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

private:
   std::unique_ptr<QMenu> mFileMenu;
   std::unique_ptr<QMenu> mViewMenu;

   std::unique_ptr<QWidget> mTagListViewWidget;
   std::unique_ptr<QWidget> mTagSocketListViewWidget;
};

#endif // MENUBAR_H
