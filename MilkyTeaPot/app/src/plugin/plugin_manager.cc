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

void Manager::ForeachOption(std::function<void(const QString *, QWidget *)> foreach_option) {
    const QString *s;
    QWidget *w;
    foreach (auto option, options_) {
        std::tie(s, w) = option();
        foreach_option(s, w);
    }
}

void Manager::SetModified() {
    main_window_.SetModified();
}

void Manager::AddViewAction(QAction *action, QAction *insert_before) {
    main_window_.AddViewAction(action, insert_before);
}

QAction *Manager::AddViewMenu(QMenu *menu, QAction *insert_before) {
    return main_window_.AddViewMenu(menu, insert_before);
}

QAction *Manager::AddViewSeparator(QAction *insert_before) {
    return main_window_.AddViewSeparator(insert_before);
}

void Manager::AddToolsAction(QAction *action, QAction *insert_before) {
    main_window_.AddToolsAction(action, insert_before);
}

QAction *Manager::AddToolsMenu(QMenu *menu, QAction *insert_before) {
    return main_window_.AddToolsMenu(menu, insert_before);
}

QAction *Manager::AddToolsSeparator(QAction *insert_before) {
    return main_window_.AddToolsSeparator(insert_before);
}

void Manager::AddPreferencesOption(std::function<std::tuple<const QString *, QWidget *>()> option) {
    options_.append(option);
}


} // namespace Plugin
