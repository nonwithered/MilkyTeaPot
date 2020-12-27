#include "config_text_edit.h"

#include "plugin/plugin_config_editor.h"

ConfigTextEdit::~ConfigTextEdit() {
    emit Plugin::ConfigEditor::Instance().SignalClosedConfigEditor();
}

ConfigTextEdit::ConfigTextEdit(QWidget* parent)
    : QTextEdit(parent)
    , sub_window_(nullptr) {
    ui.SetupUi(this);
    connect(this, SIGNAL(textChanged()), this, SLOT(SetTitleModified()));
}

QMdiSubWindow *ConfigTextEdit::SubWindow(QMdiSubWindow *w) {
    if (w != nullptr) {
        sub_window_ = w;
        ui.SetupMdi(w);
    }
    return sub_window_;
}

void ConfigTextEdit::SetTitleModified() {
    setWindowModified(true);
}
