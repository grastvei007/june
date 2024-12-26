#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <map>

#include <QMainWindow>

class ClimateData;
class TriggerData;
class QListWidget;
class QListWidgetItem;
class QNetworkAccessManager;


namespace Ui {
class MainWindow;
}

class MenuBar;
class StatusBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QNetworkAccessManager& nam, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onListItemClicked(QListWidgetItem *aItem);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager& networkAccessManager_;

    std::unique_ptr<MenuBar> mMenuBar;
    std::unique_ptr<StatusBar> mStatusBar;
    std::unique_ptr<QListWidget> mListWidget;

    ClimateData *mClimateData = nullptr;
    TriggerData *mTriggerData = nullptr;

    std::map<QString, std::shared_ptr<QWidget>> centralWidgets_;
};

#endif // MAINWINDOW_H
