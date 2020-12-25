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

Manager::Manager(MainWindow *main_window)
    : QObject(main_window)
    , main_window_(*main_window) {
    if (instance_ != nullptr) {
        return;
    }
    instance_ = this;
    OnLoad();
    OnAttach();
    Connect();
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
        loaders_.insert(key, loader);
    }
}

void Manager::OnAttach() {
    foreach (BasePlugin *plugin, plugins_) {
        plugin->OnAttach(plugins_, callbacks_);
    }
}

void Manager::OnUnload() {
    foreach (QString key, plugins_.keys()) {
        plugins_.find(key).value()->OnUnload();
        loaders_.find(key).value()->unload();
    }
}

Callbacks &Manager::GetCallbacks() {
    return callbacks_;
}

void Manager::Connect() {
    set_modified_ = [=] () -> void {
        main_window_.SetModified();
    };
    add_view_action_ = [=] (QAction *action, QAction *insert_before) -> void {
        main_window_.AddViewAction(action, insert_before);
    };
    add_view_menu_ = [=] (QMenu *menu, QAction *insert_before) -> QAction * {
        return main_window_.AddViewMenu(menu, insert_before);
    };
    add_view_separator_ = [=] (QAction *insert_before) -> QAction * {
        return main_window_.AddViewSeparator(insert_before);
    };
    add_tools_action_ = [=] (QAction *action, QAction *insert_before) -> void {
        main_window_.AddToolsAction(action, insert_before);
    };
    add_tools_menu_ = [=] (QMenu *menu, QAction *insert_before) -> QAction * {
        return main_window_.AddToolsMenu(menu, insert_before);
    };
    add_tools_separator_ = [=] (QAction *insert_before) -> QAction * {
        return main_window_.AddToolsSeparator(insert_before);
    };
}

} // namespace Plugin
