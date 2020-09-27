#include "menubar.h"

#include <QMenu>
#include <QAction>
#include <QSettings>

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
