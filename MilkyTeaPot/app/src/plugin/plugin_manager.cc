#include "plugin_manager.h"

#include <QApplication>
#include <QDir>

#include "plugin_base.h"
#include "../../settings.h"

namespace Plugin {

Manager &Manager::Instance() {
    return *instance_;
}

Manager *Manager::instance_ = nullptr;

Manager::Manager(QObject *parent)
    : QObject(parent) {
    if (instance_ != nullptr) {
        return;
    }
    OnLoad();
    OnAttach();
    instance_ = this;
}

Manager::~Manager() {
    OnUnload();
}

void Manager::OnLoad() {
    QDir bin_dir(QCoreApplication::applicationDirPath());
    QDir root_dir(bin_dir.absoluteFilePath(".."));
    if (!root_dir.exists(kPluginsDir)) {
        root_dir.mkdir(kPluginsDir);
    }
    QDir plugins_dir = root_dir.absoluteFilePath(kPluginsDir);
    foreach (QString instance_name, plugins_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QDir instancen_dir = plugins_dir.absoluteFilePath(instance_name);
        QPluginLoader *loader = new QPluginLoader(instancen_dir.absoluteFilePath(instance_name));
        if (!loader->load()) {
            delete loader;
        }
        BasePlugin *instance = qobject_cast<BasePlugin *>(loader->instance());
        QString key = instance->OnLoad(instancen_dir);
        plugins_.insert(key, instance);
        loader->setParent(this);
        loaders_.insert(key, loader);
    }
}

void Manager::OnAttach() {
    foreach (BasePlugin *plugin, plugins_) {
        plugin->OnAttach(plugins_, base_events_);
    }
}

void Manager::OnUnload() {
    foreach (QString key, plugins_.keys()) {
        plugins_.find(key).value()->OnUnload();
        loaders_.find(key).value()->unload();
    }
}

} // namespace Plugin
