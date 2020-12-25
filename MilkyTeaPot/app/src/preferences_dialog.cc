#include "preferences_dialog.h"

#include "plugin/plugin_manager.h"

PreferencesDialog::PreferencesDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f) {
    ui.SetupUi(this);
    Plugin::Manager::Instance().ForeachOption([=] (const QString *s, QWidget *w) -> void {
        w->setParent(this);
        ui.list_widget->addItem(*s);
        ui.stacked_layout->addWidget(w);
    });
}

PreferencesDialog::~PreferencesDialog() {
}
