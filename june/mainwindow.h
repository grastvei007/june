#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <map>

#include <QMainWindow>

class ClimateData;
class TriggerData;
class QListWidget;
class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MenuBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onListItemClicked(QListWidgetItem *aItem);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<MenuBar> mMenuBar;
    std::unique_ptr<QListWidget> mListWidget;

    ClimateData *mClimateData = nullptr;
    TriggerData *mTriggerData = nullptr;
};

#endif // MAINWINDOW_H
