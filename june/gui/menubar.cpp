#include "menubar.h"

#include <QMenu>
#include <QAction>

#include <tagsystem/taglistview.h>
#include <tagsystem/tagsocketlistview.h>

MenuBar::MenuBar()
{
    mFileMenu = std::make_unique<QMenu>("File", this);

    addMenu(mFileMenu.get());

    mViewMenu = std::make_unique<QMenu>("View", this);

    QAction *tagListViewAction = mViewMenu->addAction("Tag List");
    connect(tagListViewAction, &QAction::triggered, this, &MenuBar::onTagListClicked);

    QAction *tagSocketListAction = mViewMenu->addAction("TagSocket List");
    connect(tagSocketListAction, &QAction::triggered, this, &MenuBar::onTagSocketListClicked);

    addMenu(mViewMenu.get());
}

void MenuBar::onTagListClicked(bool)
{
    if(!mTagListViewWidget)
        mTagListViewWidget.reset(new TagListView);

    mTagListViewWidget->setVisible(true);
    mTagListViewWidget->raise();
}

void MenuBar::onTagSocketListClicked(bool)
{
    if(!mTagSocketListViewWidget)
        mTagSocketListViewWidget.reset(new TagSocketListView);

    mTagSocketListViewWidget->setVisible(true);
    mTagSocketListViewWidget->raise();
}
