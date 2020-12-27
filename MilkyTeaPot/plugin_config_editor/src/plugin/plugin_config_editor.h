#ifndef PLUGIN_CONFIG_EDITER_H
#define PLUGIN_CONFIG_EDITER_H

#include <QObject>
#include <QAction>

#include "../app/src/plugin/plugin_base.h"
#include "../config_text_edit.h"

namespace Plugin {

class ConfigEditor : public QObject, public PluginInterface {
    Q_OBJECT

    Q_PLUGIN_METADATA(IID PluginInterface_iid)
    Q_INTERFACES(Plugin::PluginInterface)

signals:
    void SignalClosedConfigEditor();

public:
    static ConfigEditor &Instance(ConfigEditor *self = nullptr);

public:
    ~ConfigEditor();
    ConfigEditor();

public:
    QString OnLoad(QDir &) final;
    void OnAttach(const QHash<QString, PluginInterface *> &plugins, Callbacks *callbacks) final;
    void OnUnload() final;

private:
    void AddViewMenu();
    void AddToolsMenu();

public:
    bool IsShowingTextEditor();

private slots:
    void SetShowGrid(bool);
    void SetClosedConfigEditor();
    void ApplyModify();

private:
    ConfigTextEdit *text_edit_;
    QMdiSubWindow *sub_window_;
    QAction *action_check_show_editor_;
    QAction *action_apply_modify_;

private:
    Callbacks *callbacks_;
};

} // namespace Plugin

#endif // PLUGIN_CONFIG_EDITER_H
