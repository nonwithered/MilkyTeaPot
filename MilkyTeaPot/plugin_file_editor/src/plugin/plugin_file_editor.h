#ifndef PLUGIN_FILE_EDITER_H
#define PLUGIN_FILE_EDITER_H

#include <QObject>
#include <QAction>

#include "../app/src/plugin/plugin_base.h"

namespace Plugin {

class FileEditor : public QObject, public PluginInterface {
    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid)
    Q_INTERFACES(Plugin::PluginInterface)

signals:
    void SignalClosedTextEditor();

public:
    static FileEditor &Instance(FileEditor *self = nullptr);

public:
    ~FileEditor();
    FileEditor();

public:
    QString OnLoad(QDir &) final;
    void OnAttach(const QHash<QString, PluginInterface *> &plugins, Callbacks *callbacks) final;
    void OnUnload() final;

private:
    void AddViewMenu();

public:
    bool IsShowingTextEditor();

private slots:
    void SetShowGrid(bool);
    void SetClosedTextEditor();

private:
    QMdiSubWindow *text_editor_;
    QAction *action_check_show_editor_;

private:
    Callbacks *callbacks_;
};

} // namespace Plugin

#endif // PLUGIN_FILE_EDITER_H
