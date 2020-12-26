#include "plugin_file_editor.h"

#include "../../settings.h"
#include "../text_file_manager.h"
#include "../text_file_editor.h"

namespace Plugin {

FileEditor &FileEditor::Instance(FileEditor *self) {
    static FileEditor *instance = self;
    return *instance;
}

FileEditor::~FileEditor() {
}

FileEditor::FileEditor()
    : QObject()
    , PluginInterface()
    , text_editor_(nullptr) {
    Instance(this);
}

QString FileEditor::OnLoad(QDir &) {
    TextFileManager::Instance(this);
    return QString::fromUtf8(kPluginName);
}

void FileEditor::OnAttach(const QHash<QString, PluginInterface *> &, Callbacks *callbacks) {
    callbacks_ = callbacks;
    connect(callbacks, SIGNAL(SignalNew()), &TextFileManager::Instance(), SLOT(New()));
    connect(callbacks, SIGNAL(SignalOpen(QFile &)), &TextFileManager::Instance(), SLOT(Open(QFile &)));
    connect(callbacks, SIGNAL(SignalSave(QFile &)), &TextFileManager::Instance(), SLOT(Save(QFile &)));
    connect(callbacks, SIGNAL(SignalClose()), &TextFileManager::Instance(), SLOT(Close()));
    AddViewMenu();
}

void FileEditor::OnUnload() {
}

void FileEditor::AddViewMenu() {
    action_check_show_editor_ = new QAction(tr("Text File Editor"), this);
    action_check_show_editor_->setCheckable(true);
    action_check_show_editor_->setChecked(IsShowingTextEditor());
    action_check_show_editor_->setStatusTip(tr(kTipCheckShowEditor));
    connect(action_check_show_editor_, SIGNAL(toggled(bool)), this, SLOT(SetShowGrid(bool)));
    connect(this, SIGNAL(SignalClosedTextEditor()), this, SLOT(SetClosedTextEditor()));
    callbacks_->AddViewAction(action_check_show_editor_);
}

bool FileEditor::IsShowingTextEditor() {
    return text_editor_ != nullptr;
}

void FileEditor::SetShowGrid(bool b) {
    if (b == IsShowingTextEditor()) {
        return;
    }
    if (b) {
        TextFileEditor *w = new TextFileEditor;
        w->setAttribute(Qt::WA_DeleteOnClose);
        text_editor_ = callbacks_->AddCentralSubWindow(w);
        text_editor_->show();
    } else {
        text_editor_->close();
    }
}

void FileEditor::SetClosedTextEditor() {
    text_editor_ = nullptr;
    action_check_show_editor_->setChecked(false);
}

} // namespace Plugin
