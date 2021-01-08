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
    void SetupUi(QMainWindow *);

public:
    QMdiArea *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

};

} // namespace Ui

#endif // ifndef UI_MAIN_WINDOW_H
