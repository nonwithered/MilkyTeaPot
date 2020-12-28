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

public:
    static ConfigEditor &Instance(ConfigEditor *p = nullptr);

signals:
    void SignalShowConfigEditor(bool);

public:
    ~ConfigEditor();
    ConfigEditor();

public:
    QString OnLoad(QDir &) final;
    void OnAttach(const QHash<QString, PluginInterface *> &plugins, Callbacks *callbacks) final;
    void OnUnload() final;

private:
    void PreferenceRead();
    void PreferenceWrite();
    void AddViewMenu();
    void AddToolsMenu();
    void AddPreferenceOption();
    void WarningApplyFailed();
    bool IsShowing();

private slots:
    void SetShow(bool);
    void ApplyModify();
    void Refresh();
    void OnOpen();
    void OnClose();
    void OnQuit();

private:
    ConfigTextEdit *text_edit_;
    QAction *action_check_show_editor_;
    QAction *action_apply_modify_;
    QString load_dir_;
    bool quitted_;

private:
    Callbacks *callbacks_;
};

} // namespace Plugin

#endif // PLUGIN_CONFIG_EDITER_H
