#include "ui_main_window.h"

#include <QGuiApplication>
#include <QScreen>
#include <QMdiSubWindow>

#include "../../settings.h"

namespace Ui {

void Ui_MainWindow::SetupUi(QMainWindow *main_window) {
    if (main_window->objectName().isEmpty()) {
        main_window->setObjectName(QString::fromUtf8("Ui_MainWindow"));
    }

    QRect rect = QGuiApplication::screens().at(0)->availableGeometry();
    int width = rect.width() * 3 / 4;
    int height = rect.height() * 3 / 4;
    main_window->resize(width, height);
    main_window->setWindowState(main_window->windowState() | Qt::WindowMaximized);

    centralwidget = new QMdiArea(main_window);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    main_window->setCentralWidget(centralwidget);

    menubar = new QMenuBar(main_window);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    main_window->setMenuBar(menubar);

    statusbar = new QStatusBar(main_window);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    main_window->setStatusBar(statusbar);

    main_window->setWindowTitle(kAppName);

    QMetaObject::connectSlotsByName(main_window);
}

} // namespace Ui
