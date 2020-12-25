#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>
#include <QMap>
#include <QPluginLoader>

#include <functional>

#include "plugin_base.h"
#include "../mainwindow.h"

namespace Plugin {

class Manager : public QObject {
    Q_OBJECT

    friend class Callbacks;

public:
    static Manager &Instance();

private:
    static Manager *instance_;

public:
    Manager(MainWindow *main_window);
    ~Manager();

public:
    Callbacks &GetCallbacks();

private:
    void OnLoad();
    void OnAttach();
    void OnUnload();
    void Connect();

private:
    MainWindow &main_window_;
    Callbacks callbacks_;
    QHash<QString, BasePlugin *> plugins_;
    QHash<QString, QPluginLoader *> loaders_;

private:
    std::function<void()> set_modified_;
    std::function<void(QAction *, QAction *)> add_view_action_;
    std::function<QAction *(QMenu *, QAction *)> add_view_menu_;
    std::function<QAction *(QAction *)> add_view_separator_;
    std::function<void(QAction *, QAction *)> add_tools_action_;
    std::function<QAction *(QMenu *, QAction *)> add_tools_menu_;
    std::function<QAction *(QAction *)> add_tools_separator_;

private:
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    Manager &operator=(const Manager &) = delete;
    Manager &operator=(Manager &&) = delete;
};

} // namespace Plugin

#endif // PLUGIN_MANAGER_H
