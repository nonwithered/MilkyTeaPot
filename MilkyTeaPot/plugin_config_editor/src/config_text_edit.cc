#include "config_text_edit.h"

#include "plugin/plugin_config_editor.h"
#include "preference_item.h"

ConfigTextEdit::~ConfigTextEdit() {
    emit Plugin::ConfigEditor::Instance().SignalShowConfigEditor(false);
}

ConfigTextEdit::ConfigTextEdit(QWidget* parent)
    : QTextEdit(parent)
    , sub_window_(nullptr) {
    ui.SetupUi(this);
    connect(this, SIGNAL(textChanged()), this, SLOT(SetTitleModified()));
    connect(&PreferenceItem::Instance(), SIGNAL(Modified()), this, SLOT(OnOptionModified()));
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

void ConfigTextEdit::OnOptionModified() {
    if (!PreferenceItem::Instance().show_editor) {
        close();
        return;
    }
    setFont(QFont(PreferenceItem::Instance().font_family, PreferenceItem::Instance().font_size));
    if (sub_window_ != nullptr) {
        sub_window_->resize(PreferenceItem::Instance().width, PreferenceItem::Instance().height);
        sub_window_->move(PreferenceItem::Instance().position_x, PreferenceItem::Instance().position_y);
    }
}
