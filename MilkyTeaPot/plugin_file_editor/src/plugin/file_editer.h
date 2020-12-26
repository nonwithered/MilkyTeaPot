#ifndef FILE_EDITER_H
#define FILE_EDITER_H

#include <QObject>

#include "base_plugin.h"

namespace Plugin {

class FileEditor : public QObject, public AbstractPlugin {
    Q_OBJECT

    Q_PLUGIN_METADATA(IID AbstractPlugin_iid)
    Q_INTERFACES(Plugin::AbstractPlugin)

public:
    FileEditor();
    ~FileEditor() override;

public:
    QString OnLoad(QDir &) final;
    void OnAttach(QHash<QString, AbstractPlugin *> &, Callbacks *) final;
    void OnUnload() final;
};

} // namespace Plugin

#endif // FILE_EDITER_H
