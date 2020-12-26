#include "file_editer.h"

#include <QDebug>

#include "../../settings.h"

namespace Plugin {

FileEditor::FileEditor()
    : QObject()
    , PluginInterface() {
    qDebug() << "ctor";
}

FileEditor::~FileEditor() {
    qDebug() << "dtor";
}

QString FileEditor::OnLoad(QDir &) {
    qDebug() << "OnLoad";
    return QString::fromUtf8(kPluginName);
}

void FileEditor::OnAttach(QHash<QString, PluginInterface *> &, Callbacks *) {
    qDebug() << "OnAttach";
}

void FileEditor::OnUnload() {
    qDebug() << "OnUnload";
}

} // namespace Plugin
