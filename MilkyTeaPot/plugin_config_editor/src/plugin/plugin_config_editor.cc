#include "plugin_config_editor.h"

#include <QMessageBox>
#include <QTextStream>
#include <QJsonDocument>
#include <QTextCodec>

#include "../../settings.h"
#include "../config_text_edit.h"
#include "../preference_item.h"

namespace Plugin {

ConfigEditor &ConfigEditor::Instance(ConfigEditor *p) {
    static ConfigEditor *instance = p;
    return *instance;
}

ConfigEditor::~ConfigEditor() {
}

ConfigEditor::ConfigEditor()
    : QObject()
    , PluginInterface()
    , text_edit_(nullptr),
    quitted_(false) {
    Instance(this);
}

QString ConfigEditor::OnLoad(QDir &dir) {
    load_dir_ = dir.absolutePath();
    PreferenceRead();
    return QString::fromUtf8(kPluginName);
}

void ConfigEditor::OnAttach(const QHash<QString, PluginInterface *> &, Callbacks *callbacks) {
    callbacks_ = callbacks;
    connect(callbacks_, SIGNAL(SignalModified()), this, SLOT(Refresh()));
    connect(callbacks_, SIGNAL(SignalNew()), this, SLOT(OnOpen()));
    connect(callbacks_, SIGNAL(SignalOpen(QFile &)), this, SLOT(OnOpen()));
    connect(callbacks_, SIGNAL(SignalClose()), this, SLOT(OnClose()));
    connect(callbacks_, SIGNAL(SignalQuit()), this, SLOT(OnQuit()));
    connect(this, SIGNAL(SignalClosedConfigEditor()), this, SLOT(SetClosed()));
    AddViewMenu();
    AddToolsMenu();
}

void ConfigEditor::OnUnload() {
    PreferenceWrite();
}

void ConfigEditor::PreferenceRead() {
    PreferenceItem::Instance(this);
    QDir dir = load_dir_;
    if (!dir.exists()) {
        return;
    }
    QFile file(dir.absoluteFilePath(QString::fromUtf8(kSettingsFileName)));
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isObject()) {
        return;
    }
    PreferenceItem::Instance().FromJson(doc.object());
}

void ConfigEditor::PreferenceWrite() {
    QDir dir = load_dir_;
    if (!dir.exists()) {
        return;
    }
    QFile file(dir.absoluteFilePath(QString::fromUtf8(kSettingsFileName)));
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QJsonDocument doc(PreferenceItem::Instance().ToJson());
    file.write(doc.toJson());
    file.close();
}

void ConfigEditor::AddViewMenu() {
    callbacks_->AddViewSeparator();
    action_check_show_editor_ = new QAction(tr(kPluginName), this);
    action_check_show_editor_->setCheckable(true);
    action_check_show_editor_->setStatusTip(tr(kTipCheckShowEditor));
    action_check_show_editor_->setEnabled(false);
    if (PreferenceItem::Instance().show_editor) {
        action_check_show_editor_->setChecked(true);
        text_edit_ = new ConfigTextEdit;
        text_edit_->setAttribute(Qt::WA_DeleteOnClose);
        text_edit_->SubWindow(callbacks_->AddCentralSubWindow(text_edit_));
    }
    connect(action_check_show_editor_, SIGNAL(toggled(bool)), this, SLOT(SetShow(bool)));
    callbacks_->AddViewAction(action_check_show_editor_);
}

void ConfigEditor::AddToolsMenu() {
    callbacks_->AddToolsSeparator();
    action_apply_modify_ = new QAction(tr(kApplyModify), this);
    action_apply_modify_->setEnabled(false);
    action_apply_modify_->setStatusTip(tr(kTipApplyModify));
    connect(action_apply_modify_, SIGNAL(triggered()), this, SLOT(ApplyModify()));
    callbacks_->AddToolsAction(action_apply_modify_);
}

void ConfigEditor::WarningApplyFailed() {
    QMessageBox::warning(callbacks_->GetMainWindow(), tr(kApplyModify), tr(kMsgApplyFailed));
}

bool ConfigEditor::IsShowing() {
    return text_edit_ != nullptr;
}

void ConfigEditor::SetShow(bool b) {
    if (b == IsShowing()) {
        if (!b) {
            if (!quitted_) {
                PreferenceItem::Instance().show_editor = false;
                action_apply_modify_->setEnabled(false);
            }
        }
        return;
    }
    if (b) {
        PreferenceItem::Instance().show_editor = true;
        action_apply_modify_->setEnabled(true);
        text_edit_ = new ConfigTextEdit;
        text_edit_->setAttribute(Qt::WA_DeleteOnClose);
        text_edit_->SubWindow(callbacks_->AddCentralSubWindow(text_edit_));
        text_edit_->SubWindow()->show();
        Refresh();
        text_edit_->setWindowModified(false);
    } else {
        text_edit_->SubWindow()->close();
    }
}

void ConfigEditor::SetClosed() {
    text_edit_ = nullptr;
    action_check_show_editor_->setChecked(false);
}

void ConfigEditor::ApplyModify() {
    QString text = text_edit_->toPlainText();
    QByteArray bytes = text.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    if (!doc.isObject()) {
        WarningApplyFailed();
        return;
    }
    callbacks_->GetConfig() = doc.object();
    callbacks_->EmitModified();
    text_edit_->setWindowModified(false);
}

void ConfigEditor::Refresh() {
    if (!IsShowing()) {
        return;
    }
    QJsonDocument doc(callbacks_->GetConfig());
    QByteArray bytes = doc.toJson();
    QString text = QTextCodec::codecForName("UTF-8")->toUnicode(bytes);
    text_edit_->setText(text);
}

void ConfigEditor::OnOpen() {
    action_check_show_editor_->setEnabled(true);
    if (IsShowing()) {
        text_edit_->SubWindow()->show();
        Refresh();
        text_edit_->setWindowModified(false);
        action_apply_modify_->setEnabled(true);
    }
}

void ConfigEditor::OnClose() {
    action_check_show_editor_->setEnabled(false);
    if (IsShowing()) {
        text_edit_->SubWindow()->hide();
        text_edit_->setText(QString());
        action_apply_modify_->setEnabled(false);
    }
}

void ConfigEditor::OnQuit() {
    quitted_ = true;
}

} // namespace Plugin
