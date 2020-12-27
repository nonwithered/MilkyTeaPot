#include "config_text_edit.h"
#include "plugin/plugin_config_editor.h"

ConfigTextEdit::~ConfigTextEdit() {
    emit Plugin::ConfigEditor::Instance().SignalClosedConfigEditor();
}

ConfigTextEdit::ConfigTextEdit(QWidget* parent)
    : QTextEdit(parent) {
    ui.SetupUi(this);
}
