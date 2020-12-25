#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>

#include "ui/ui_mainwindow.h"

#include "file_holder.h"

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
    void ToolsOptions();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void CreateActions();
    void CreateMenus();

private:
    Ui::MainWindow ui;
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
    QAction *action_tools_options;

private:
    FileHolder *file_holder_;
};

#endif // ifndef MAINWINDOW_H
