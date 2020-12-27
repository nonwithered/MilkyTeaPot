#include "main_window.h"

#include <QKeySequence>
#include <QMessageBox>
#include <QFileDialog>

#include "settings.h"
#include "preferences_dialog.h"

void MainWindow::FileNew() {
    if (!FileClose()) {
        return;
    }
    config_manager_->New();
    setWindowTitle(tr("[*]%1 - %2").arg(tr(kUntitled))
                                   .arg(tr(kAppName)));
}

bool MainWindow::FileOpen() {
    if (!FileClose()) {
        return false;
    }
    QString file_name = QFileDialog::getOpenFileName(this, tr("open"), ".", tr("Json Files (*" kConfigSuffix ")" ";; All Files (*.*)"));
    if (file_name.isEmpty()) {
        return false;
    }
    if (!config_manager_->Open(file_name)) {
        QMessageBox::warning(this, tr("Open"), file_name + tr(kWarnOpen));
        return false;
    }
    setWindowTitle(tr("[*]%1 - %2").arg(file_name)
                                   .arg(tr(kAppName)));
    return true;
}

bool MainWindow::FileSave() {
    if (!isWindowModified()) {
        return true;
    }
    if (config_manager_->Available()) {
        if (!config_manager_->Save()) {
            return false;
        }
        setWindowModified(false);
        return true;
    } else {
        return FileSaveAs();
    }
}

bool MainWindow::FileSaveAs() {
    QString file_name = QFileDialog::getSaveFileName(this, tr("save as"), ".", tr("Json Files (*" kConfigSuffix ")" ";; All Files (*.*)"));
    if (file_name.isEmpty()) {
        return false;
    }
    if (!config_manager_->SaveAs(file_name)) {
        return false;
    }
    setWindowModified(false);
    setWindowTitle(tr("[*]%1 - %2").arg(file_name)
                                   .arg(tr(kAppName)));
    return true;
}

bool MainWindow::FileClose() {
    if (!isWindowModified()) {
        config_manager_->Close();
        setWindowTitle(kAppName);
        return true;
    }
    int r = QMessageBox::question(this, tr("continue"),
                                 tr(kWarnMidified "\n" kQuestChanges),
                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    switch (r) {
    case QMessageBox::Yes:
        if (!FileSave()) {
            return false;
        }
        config_manager_->Close();
        setWindowTitle(kAppName);
        return true;
    case QMessageBox::No:
        config_manager_->Close();
        setWindowTitle(kAppName);
        return true;
    default:
        return false;
    }
}

void MainWindow::FileQuit() {
    if (!FileClose()) {
        return;
    }
    close();
}

void MainWindow::EditUndo() {

}

void MainWindow::EditRedo() {

}

void MainWindow::ToolsPreferences() {
    QDialog *dialog = new PreferencesDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}

MainWindow::~MainWindow() {
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , config_manager_(new ConfigManager(this)) {
    ui.SetupUi(this);
    CreateActions();
    CreateMenus();
}

void MainWindow::CreateActions() {
    action_file_new = new QAction(tr("&New"), this);
    action_file_new->setShortcut(QKeySequence::New);
    action_file_new->setStatusTip(tr("new file"));
    connect(action_file_new, SIGNAL(triggered()), this, SLOT(FileNew()));

    action_file_open = new QAction(tr("&Open"), this);
    action_file_open->setShortcut(QKeySequence::Open);
    action_file_open->setStatusTip(tr("open file"));
    connect(action_file_open, SIGNAL(triggered()), this, SLOT(FileOpen()));

    action_file_save = new QAction(tr("&Save"), this);
    action_file_save->setShortcut(QKeySequence::Save);
    action_file_save->setStatusTip(tr("save file"));
    connect(action_file_save, SIGNAL(triggered()), this, SLOT(FileSave()));

    action_file_save_as = new QAction(tr("Save &As"), this);
    action_file_save_as->setShortcut(QKeySequence::SaveAs);
    action_file_save_as->setStatusTip(tr("save as file"));
    connect(action_file_save_as, SIGNAL(triggered()), this, SLOT(FileSaveAs()));

    action_file_close = new QAction(tr("&Close"), this);
    action_file_close->setShortcut(QKeySequence::Close);
    action_file_close->setStatusTip(tr("close file"));
    connect(action_file_close, SIGNAL(triggered()), this, SLOT(FileClose()));

    action_file_quit = new QAction(tr("&Quit"), this);
    action_file_quit->setShortcut(QKeySequence::Quit);
    action_file_quit->setStatusTip(tr("quit"));
    connect(action_file_quit, SIGNAL(triggered()), this, SLOT(FileQuit()));

    action_edit_undo = new QAction(tr("&Undo"), this);
    action_edit_undo->setShortcut(QKeySequence::Undo);
    action_edit_undo->setStatusTip(tr("undo"));
    connect(action_edit_undo, SIGNAL(triggered()), this, SLOT(EditUndo()));

    action_edit_redo = new QAction(tr("&Redo"), this);
    action_edit_redo->setShortcut(QKeySequence::Redo);
    action_edit_redo->setStatusTip(tr("redo"));
    connect(action_edit_redo, SIGNAL(triggered()), this, SLOT(EditRedo()));

    action_tools_preferences = new QAction(tr("&Preferences"), this);
    action_tools_preferences->setStatusTip(tr("preferences"));
    connect(action_tools_preferences, SIGNAL(triggered()), this, SLOT(ToolsPreferences()));
}

void MainWindow::CreateMenus() {
    menu_file = ui.menubar->addMenu(tr("&File"));
    menu_file->addAction(action_file_new);
    menu_file->addAction(action_file_open);
    menu_file->addAction(action_file_save);
    menu_file->addAction(action_file_save_as);
    menu_file->addSeparator();
    menu_file->addAction(action_file_close);
    menu_file->addAction(action_file_quit);

    menu_edit = ui.menubar->addMenu(tr("&Edit"));
    menu_edit->addAction(action_edit_undo);
    menu_edit->addAction(action_edit_redo);

    menu_view = ui.menubar->addMenu(tr("&View"));

    menu_tools = ui.menubar->addMenu(tr("&Tools"));
    menu_tool_separator = menu_tools->addSeparator();
    menu_tools->addAction(action_tools_preferences);
}

ConfigManager &MainWindow::GetConfigManager() {
    return *config_manager_;
}

void MainWindow::SetModified() {
    setWindowModified(true);
}

void MainWindow::AddViewAction(QAction *action, QAction *insert_before) {
    action->setParent(this);
    menu_view->insertAction(insert_before, action);
}


QAction *MainWindow::AddViewMenu(QMenu *menu, QAction *insert_before) {
    menu->setParent(this);
    return menu_view->insertMenu(insert_before, menu);
}

QAction *MainWindow::AddViewSeparator(QAction *insert_before) {
    return menu_view->insertSeparator(insert_before);
}

void MainWindow::AddToolsAction(QAction *action, QAction *insert_before) {
    action->setParent(this);
    if (insert_before == nullptr) {
        insert_before = menu_tool_separator;
    }
    menu_tools->insertAction(insert_before, action);
}

QAction *MainWindow::AddToolsMenu(QMenu *menu, QAction *insert_before) {
    menu->setParent(this);
    if (insert_before == nullptr) {
        insert_before = menu_tool_separator;
    }
    return menu_tools->insertMenu(insert_before, menu);
}

QAction *MainWindow::AddToolsSeparator(QAction *insert_before) {
    if (insert_before == nullptr) {
        insert_before = menu_tool_separator;
    }
    return menu_tools->insertSeparator(insert_before);
}

QMdiSubWindow *MainWindow::AddCentralSubWindow(QWidget *w) {
    return ui.centralwidget->addSubWindow(w);
}
