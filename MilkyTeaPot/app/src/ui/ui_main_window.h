#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QWidget>
#include <QMdiArea>

namespace Ui {

class Ui_MainWindow {

public:
    ~Ui_MainWindow() = default;
    Ui_MainWindow() = default;

private:
    Ui_MainWindow(const Ui_MainWindow &) = delete;
    Ui_MainWindow(Ui_MainWindow &&) = delete;
    Ui_MainWindow &operator=(const Ui_MainWindow &) = delete;
    Ui_MainWindow &operator=(Ui_MainWindow &&) = delete;

public:
    void SetupUi(QMainWindow *);

public:
    QMdiArea *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

};

} // namespace Ui

#endif // ifndef UI_MAIN_WINDOW_H
