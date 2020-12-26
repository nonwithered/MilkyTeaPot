#include <QApplication>

#include "plugin/plugin_manager.h"
#include "main_window.h"

#include <QDialog>
#include <QListWidget>
#include <QStackedLayout>
#include <QGridLayout>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    Plugin::Manager::Instance(&w);
    w.show();
    return a.exec();
}
