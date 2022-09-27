#include "menubar.h"

#include <QMenu>
#include <QAction>
#include <QSettings>

#include <tagsystem/taglistview.h>
#include <tagsystem/tagsocketlistview.h>
#include <tagsystem/serverconnectwidget.h>
#include <tagsystem/taglist.h>

MenuBar::MenuBar()
{
    fileMenu_ = std::make_unique<QMenu>("File", this);

    connectToServerAction_ = std::make_unique<QAction>("Connect to server");
    disconnectFromServerAction_ = std::make_unique<QAction>("Disconnect from server");

    fileMenu_->addAction(connectToServerAction_.get());
    fileMenu_->addAction(disconnectFromServerAction_.get());


    addMenu(fileMenu_.get());

    mViewMenu = std::make_unique<QMenu>("View", this);

    QAction *tagListViewAction = mViewMenu->addAction("Tag List");
    connect(tagListViewAction, &QAction::triggered, this, &MenuBar::onTagListClicked);

    QAction *tagSocketListAction = mViewMenu->addAction("TagSocket List");
    connect(tagSocketListAction, &QAction::triggered, this, &MenuBar::onTagSocketListClicked);

    addMenu(mViewMenu.get());

    connect(connectToServerAction_.get(), &QAction::triggered, this, &MenuBar::onConnectToServerClicked);
    connect(disconnectFromServerAction_.get(), &QAction::triggered, this, &MenuBar::onDisconnectFromServerClicked);
}

void MenuBar::onTagListClicked(bool)
{
    if(!mTagListViewWidget)
    {
        mTagListViewWidget.reset(new TagListView);
        connect(mTagListViewWidget.get(), &QWidget::destroyed, [&](){
            QSettings settings("June", "June");
            settings.setValue("taglistwidget/size", mTagListViewWidget->size());
        });

        QSettings settings("June", "June");
        QSize size = settings.value("taglistwidget/size").toSize();
        if(size.isValid())
            mTagListViewWidget->resize(size);
    }

    mTagListViewWidget->setVisible(true);
    mTagListViewWidget->raise();
}

void MenuBar::onTagSocketListClicked(bool)
{
    if(!mTagSocketListViewWidget)
    {
        mTagSocketListViewWidget.reset(new TagSocketListView);

        connect(mTagSocketListViewWidget.get(), &QWidget::destroyed, [&](){
            QSettings settings("June", "June");
            settings.setValue("tagsocketlistwidget/size", mTagListViewWidget->size());
        });

        QSettings settings("June", "June");
        QSize size = settings.value("tagsocketlistwidget/size").toSize();
        if(size.isValid())
            mTagSocketListViewWidget->resize(size);
    }
    mTagSocketListViewWidget->setVisible(true);
    mTagSocketListViewWidget->raise();
}

void MenuBar::onConnectToServerClicked(bool)
{
    ServerConnectWidget serverConnect;
    if(serverConnect.exec())
    {
        TagList::sGetInstance().connectToServer(serverConnect.adress(), serverConnect.port());
    }

}

void MenuBar::onDisconnectFromServerClicked(bool)
{
    TagList::sGetInstance().disconnectFromServer();
}
