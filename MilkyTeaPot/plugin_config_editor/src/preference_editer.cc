#include "preference_editer.h"

#include "preference_item.h"
#include "plugin/plugin_config_editor.h"

PreferenceEditor::~PreferenceEditor() {
}

PreferenceEditor::PreferenceEditor(QWidget* parent)
    : QWidget(parent) {
    ui.SetupUi(this);
    Refresh();
    connect(&PreferenceItem::Instance(), SIGNAL(Modified()), this, SLOT(Refresh()));
    connect(ui.apply, SIGNAL(clicked()), this, SLOT(Modify()));
}

void PreferenceEditor::Refresh() {
    ui.position_x->setValue(PreferenceItem::Instance().position_x);
    ui.position_y->setValue(PreferenceItem::Instance().position_y);
    ui.width->setValue(PreferenceItem::Instance().width);
    ui.height->setValue(PreferenceItem::Instance().height);
    int index = ui.font_family->findText(PreferenceItem::Instance().font_family);
    if (index >= 0) {
        ui.font_family->setCurrentIndex(index);
    }
    ui.font_size->setValue(PreferenceItem::Instance().font_size);
    ui.show_editor->setChecked(PreferenceItem::Instance().show_editor);
    emit Plugin::ConfigEditor::Instance().SignalShowConfigEditor(PreferenceItem::Instance().show_editor);
}

void PreferenceEditor::Modify() {
    PreferenceItem::Instance().position_x = ui.position_x->value();
    PreferenceItem::Instance().position_y = ui.position_y->value();
    PreferenceItem::Instance().width = ui.width->value();
    PreferenceItem::Instance().height = ui.height->value();
    PreferenceItem::Instance().font_family = ui.font_family->currentText();
    PreferenceItem::Instance().font_size = ui.font_size->value();
    PreferenceItem::Instance().show_editor = ui.show_editor->isChecked();
    PreferenceItem::Instance().Ensure();
}

