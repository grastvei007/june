#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

class ClimateData;
class QListWidget;

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

private:
    Ui::MainWindow *ui;

    std::unique_ptr<MenuBar> mMenuBar;
    std::unique_ptr<QListWidget> mListWidget;

    ClimateData *mClimateData = nullptr;
};

#endif // MAINWINDOW_H
