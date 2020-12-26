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

class Manager : public Callbacks {
    Q_OBJECT

public:
    static Manager &Instance();

private:
    static Manager *instance_;

public:
    void SetModified() final;
    void AddViewAction(QAction *action, QAction *insert_before = nullptr) final;
    QAction *AddViewMenu(QMenu *menu, QAction *insert_before = nullptr) final;
    QAction *AddViewSeparator(QAction *insert_before = nullptr) final;
    void AddToolsAction(QAction *action, QAction *insert_before = nullptr) final;
    QAction *AddToolsMenu(QMenu *menu, QAction *insert_before = nullptr) final;
    QAction *AddToolsSeparator(QAction *insert_before = nullptr) final;
    void AddPreferencesOption(std::function<const QString(QWidget &)> option) final;
    QMdiSubWindow *AddCentralSubWindow(QWidget *w) final;

public:
    Manager(MainWindow *main_window);
    ~Manager() override;

public:
    void ForeachOption(std::function<QWidget *()>, std::function<void(const QString &, QWidget *)>);

private:
    void OnLoad();
    void OnAttach();
    void OnUnload();

private:
    MainWindow &main_window_;
    QHash<QString, AbstractPlugin *> plugins_;
    QHash<QString, QPluginLoader *> loaders_;
    QList<std::function<const QString(QWidget &)>> options_;

private:
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    Manager &operator=(const Manager &) = delete;
    Manager &operator=(Manager &&) = delete;
};

} // namespace Plugin

#endif // PLUGIN_MANAGER_H
