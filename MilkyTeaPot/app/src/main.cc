#include <QApplication>

#include "plugin/plugin_manager.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    Plugin::Manager m(&w);
    w.show();
    return a.exec();
}
