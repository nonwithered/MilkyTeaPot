#ifndef FILE_EDITER_H
#define FILE_EDITER_H

#include <QObject>

#include "plugin_interface.h"

namespace Plugin {

class FileEditor : public QObject, public PluginInterface {
    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid)
    Q_INTERFACES(Plugin::PluginInterface)

public:
    FileEditor();
    ~FileEditor() override;

public:
    QString OnLoad(QDir &) final;
    void OnAttach(QHash<QString, PluginInterface *> &, Callbacks *) final;
    void OnUnload() final;
};

} // namespace Plugin

#endif // FILE_EDITER_H
