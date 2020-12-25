#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

namespace Ui {

class MainWindow {

public:
    MainWindow() = default;

private:
    MainWindow(const MainWindow &) = delete;
    MainWindow(MainWindow &&) = delete;
    MainWindow &operator=(const MainWindow &) = delete;
    MainWindow &operator=(MainWindow &&) = delete;

public:
    void SetupUi(QMainWindow *);

public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

};

} // namespace Ui

#endif // ifndef UI_MAINWINDOW_H
