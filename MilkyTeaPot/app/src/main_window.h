#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QWidget>

#include "ui/ui_main_window.h"
#include "config_manager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private slots:
    void FileNew();
    bool FileOpen();
    bool FileSave();
    bool FileSaveAs();
    bool FileClose();
    void FileQuit();
    void EditUndo();
    void EditRedo();
    void ToolsPreferences();

protected:
    void closeEvent(QCloseEvent *) override;

public:
    ~MainWindow();
    MainWindow(QWidget *parent = nullptr);

private:
    void CreateActions();
    void CreateMenus();

public:
    ConfigManager &GetConfigManager();
    void SetModified();
    void AddViewAction(QAction *action, QAction *insert_before);
    QAction *AddViewMenu(QMenu *menu, QAction *insert_before);
    QAction *AddViewSeparator(QAction *insert_before);
    void AddToolsAction(QAction *action, QAction *insert_before);
    QAction *AddToolsMenu(QMenu *menu, QAction *insert_before);
    QAction *AddToolsSeparator(QAction *insert_before);
    QMdiSubWindow *AddCentralSubWindow(QWidget *w);

private:
    Ui::Ui_MainWindow ui;
    QMenu *menu_file;
    QAction *action_file_new;
    QAction *action_file_open;
    QAction *action_file_save;
    QAction *action_file_save_as;
    QAction *action_file_close;
    QAction *action_file_quit;
    QMenu *menu_edit;
    QAction *action_edit_undo;
    QAction *action_edit_redo;
    QMenu *menu_view;
    QMenu *menu_tools;
    QAction *menu_tool_separator;
    QAction *action_tools_preferences;

private:
    ConfigManager *config_manager_;
};

#endif // ifndef MAIN_WINDOW_H
