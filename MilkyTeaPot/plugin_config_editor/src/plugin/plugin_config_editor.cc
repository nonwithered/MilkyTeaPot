#include "plugin_config_editor.h"

#include <QMessageBox>

#include "../../settings.h"
#include "../config_manager.h"
#include "../config_text_edit.h"

namespace Plugin {

ConfigEditor &ConfigEditor::Instance(ConfigEditor *self) {
    static ConfigEditor *instance = self;
    return *instance;
}

ConfigEditor::~ConfigEditor() {
}

ConfigEditor::ConfigEditor()
    : QObject()
    , PluginInterface()
    , text_edit_(nullptr) {
    Instance(this);
}

QString ConfigEditor::OnLoad(QDir &) {
    ConfigManager::Instance(this);
    return QString::fromUtf8(kPluginName);
}

void ConfigEditor::OnAttach(const QHash<QString, PluginInterface *> &, Callbacks *callbacks) {
    callbacks_ = callbacks;
    connect(callbacks, SIGNAL(SignalNew()), &ConfigManager::Instance(), SLOT(New()));
    connect(callbacks, SIGNAL(SignalOpen(QFile &)), &ConfigManager::Instance(), SLOT(Open(QFile &)));
    connect(callbacks, SIGNAL(SignalSave(QFile &)), &ConfigManager::Instance(), SLOT(Save(QFile &)));
    connect(callbacks, SIGNAL(SignalClose()), &ConfigManager::Instance(), SLOT(Close()));
    AddViewMenu();
    AddToolsMenu();
}

void ConfigEditor::OnUnload() {
}

void ConfigEditor::AddViewMenu() {
    callbacks_->AddViewSeparator();
    action_check_show_editor_ = new QAction(tr(kPluginName), this);
    action_check_show_editor_->setCheckable(true);
    action_check_show_editor_->setChecked(IsShowingTextEditor());
    action_check_show_editor_->setStatusTip(tr(kTipCheckShowEditor));
    connect(action_check_show_editor_, SIGNAL(toggled(bool)), this, SLOT(SetShowGrid(bool)));
    connect(this, SIGNAL(SignalClosedConfigEditor()), this, SLOT(SetClosedConfigEditor()));
    callbacks_->AddViewAction(action_check_show_editor_);
}

void ConfigEditor::AddToolsMenu() {
    callbacks_->AddToolsSeparator();
    action_apply_modify_ = new QAction(tr(kApplyModify), this);
    action_apply_modify_->setEnabled(IsShowingTextEditor());
    action_apply_modify_->setStatusTip(tr(kTipApplyModify));
    connect(action_apply_modify_, SIGNAL(triggered()), this, SLOT(ApplyModify()));
    callbacks_->AddToolsAction(action_apply_modify_);
}

bool ConfigEditor::IsShowingTextEditor() {
    return text_edit_ != nullptr;
}

void ConfigEditor::SetShowGrid(bool b) {
    if (b == IsShowingTextEditor()) {
        return;
    }
    if (b) {
        action_apply_modify_->setEnabled(true);
        text_edit_ = new ConfigTextEdit;
        text_edit_->setAttribute(Qt::WA_DeleteOnClose);
        sub_window_ = callbacks_->AddCentralSubWindow(text_edit_);
        sub_window_->show();
    } else {
        sub_window_->close();
    }
}

void ConfigEditor::SetClosedConfigEditor() {
    text_edit_ = nullptr;
    action_check_show_editor_->setChecked(false);
    action_apply_modify_->setEnabled(false);
}

void ConfigEditor::ApplyModify() {
    if (!ConfigManager::Instance().TryApply(text_edit_->toPlainText())) {
        QMessageBox::warning(callbacks_->GetMainWindow(), tr(kApplyModify), tr(kMsgApplyFailed), QMessageBox::Ok);
        return;
    }
    callbacks_->SetModified();
}

} // namespace Plugin
