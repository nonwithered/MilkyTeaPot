#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>
#include <QMap>
#include <QPluginLoader>
#include <QList>

#include <functional>

#include "plugin_base.h"
#include "../main_window.h"

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
    void ForeachOption(std::function<void(const QString *, QWidget *)>);

private:
    void OnLoad();
    void OnAttach();
    void OnUnload();

private:
    MainWindow &main_window_;
    Callbacks callbacks_;
    QHash<QString, BasePlugin *> plugins_;
    QHash<QString, QPluginLoader *> loaders_;

private:
    void SetModified();
    void AddViewAction(QAction *action, QAction *insert_before);
    QAction *AddViewMenu(QMenu *menu, QAction *insert_before);
    QAction *AddViewSeparator(QAction *insert_before);
    void AddToolsAction(QAction *action, QAction *insert_before);
    QAction *AddToolsMenu(QMenu *menu, QAction *insert_before);
    QAction *AddToolsSeparator(QAction *insert_before);
    void AddPreferencesOption(std::function<std::tuple<const QString *, QWidget *>()> option);

private:
    QList<std::function<std::tuple<const QString *, QWidget *>()>> options_;

private:
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    Manager &operator=(const Manager &) = delete;
    Manager &operator=(Manager &&) = delete;
};

} // namespace Plugin

#endif // PLUGIN_MANAGER_H
