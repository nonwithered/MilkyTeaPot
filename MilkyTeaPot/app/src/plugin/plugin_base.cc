#include "plugin_base.h"

#include "plugin_manager.h"

namespace Plugin {

Callbacks::Callbacks() {
}

Callbacks::~Callbacks() {
}

void Callbacks::SetModified() {
    Manager::Instance().SetModified();
}
void Callbacks::AddViewAction(QAction *action, QAction *insert_before) {
    Manager::Instance().AddViewAction(action, insert_before);
}

QAction *Callbacks::AddViewMenu(QMenu *menu, QAction *insert_before) {
    return Manager::Instance().AddViewMenu(menu, insert_before);
}

QAction *Callbacks::AddViewSeparator(QAction *insert_before) {
    return Manager::Instance().AddViewSeparator(insert_before);
}

void Callbacks::AddToolsAction(QAction *action, QAction *insert_before) {
    Manager::Instance().AddToolsAction(action, insert_before);
}

QAction *Callbacks::AddToolsMenu(QMenu *menu, QAction *insert_before) {
    return Manager::Instance().AddToolsMenu(menu, insert_before);
}

QAction *Callbacks::AddToolsSeparator(QAction *insert_before) {
    return Manager::Instance().AddToolsSeparator(insert_before);
}

void Callbacks::AddPreferencesOption(std::function<std::tuple<const QString *, QWidget *>()> option) {
    return Manager::Instance().AddPreferencesOption(option);
}


} // namespace Plugin
