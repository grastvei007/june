#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <map>

#include <QMainWindow>

class QListWidget;
class QListWidgetItem;
class QNetworkAccessManager;
class QNetworkRequestFactory;

class CentralWiddgetFactory;


namespace Ui {
class MainWindow;
}

class MenuBar;
class StatusBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CentralWiddgetFactory &centralWidgetFactory, QNetworkAccessManager &nam, QNetworkRequestFactory &nrf, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onListItemClicked(QListWidgetItem *aItem);

private:
    void setCentralWidgetByName(const QString &name);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<MenuBar> mMenuBar;
    std::unique_ptr<StatusBar> mStatusBar;
    std::unique_ptr<QListWidget> mListWidget;

    QNetworkAccessManager &networkAccessManager_;
    QNetworkRequestFactory &networkRequestFactory_;
    CentralWiddgetFactory &centralWidgetFactory_;
};

#endif // MAINWINDOW_H
