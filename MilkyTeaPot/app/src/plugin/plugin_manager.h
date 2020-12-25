#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>
#include <QMap>
#include <QPluginLoader>

#include "plugin_base.h"

namespace Plugin {

class Manager : public QObject {
    Q_OBJECT

public:
    static Manager &Instance();

private:
    static Manager *instance_;

public:
    Manager(QObject *parent = nullptr);
    ~Manager();
    void OnLoad();
    void OnAttach();
    void OnUnload();

private:
    BaseEvents base_events_;
    QHash<QString, BasePlugin *> plugins_;
    QHash<QString, QPluginLoader *> loaders_;

private:
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    Manager &operator=(const Manager &) = delete;
    Manager &operator=(Manager &&) = delete;
};

} // namespace Plugin

#endif // PLUGIN_MANAGER_H
