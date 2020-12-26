#include "text_file_editor.h"
#include "plugin/plugin_file_editor.h"

TextFileEditor::~TextFileEditor() {
    emit Plugin::FileEditor::Instance().SignalClosedTextEditor();
}

TextFileEditor::TextFileEditor(QWidget* parent)
    : QWidget(parent) {
    ui.SetupUi(this);
}
