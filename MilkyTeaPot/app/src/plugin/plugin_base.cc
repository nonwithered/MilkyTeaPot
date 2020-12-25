#include "plugin_base.h"

#include "plugin_manager.h"

namespace Plugin {

Callbacks::Callbacks() {
}

Callbacks::~Callbacks() {
}

void Callbacks::SetWindowModified() {
    Manager::Instance().set_modified_();
}
void Callbacks::AddViewAction(QAction *action, QAction *insert_before) {
    Manager::Instance().add_view_action_(action, insert_before);
}

QAction *Callbacks::AddViewMenu(QMenu *menu, QAction *insert_before) {
    return Manager::Instance().add_view_menu_(menu, insert_before);
}

QAction *Callbacks::AddViewSeparator(QAction *insert_before) {
    return Manager::Instance().add_view_separator_(insert_before);
}

void Callbacks::AddToolsAction(QAction *action, QAction *insert_before) {
    Manager::Instance().add_tools_action_(action, insert_before);
}

QAction *Callbacks::AddToolsMenu(QMenu *menu, QAction *insert_before) {
    return Manager::Instance().add_tools_menu_(menu, insert_before);
}

QAction *Callbacks::AddToolsSeparator(QAction *insert_before) {
    return Manager::Instance().add_tools_separator_(insert_before);
}


} // namespace Plugin
