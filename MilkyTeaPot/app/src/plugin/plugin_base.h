#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#include <QString>
#include <QHash>
#include <QDir>
#include <QFile>
#include <QAction>
#include <QMenu>
#include <QWidget>
#include <QMdiSubWindow>
#include <QJsonObject>

#include <functional>
#include <tuple>

#include "../../settings.h"

#define kInterfaceName "BasePlugin"
#define kInterfaceVersion "1.0"
#define PluginInterface_iid kAppName "." kInterfaceName "/" kInterfaceVersion

namespace Plugin {

class Callbacks : public QObject {
    Q_OBJECT

signals:
    void SignalNew();
    void SignalOpen(QFile &);
    void SignalSave(QFile &);
    void SignalClose();
    void SignalQuit();
    void SignalModified();

public:
    virtual void EmitModified() = 0;

public:
    virtual QJsonObject &GetConfig() = 0;
    virtual void AddViewAction(QAction *action, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddViewMenu(QMenu *menu, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddViewSeparator(QAction *insert_before = nullptr) = 0;
    virtual void AddToolsAction(QAction *action, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddToolsMenu(QMenu *menu, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddToolsSeparator(QAction *insert_before = nullptr) = 0;
    virtual void AddPreferencesOption(std::function<std::tuple<const QString, QWidget *>()> option) = 0;
    virtual QMdiSubWindow *AddCentralSubWindow(QWidget *w) = 0;
    virtual QWidget *GetMainWindow() = 0;

public:
    ~Callbacks();
    Callbacks(QObject *parent = nullptr);

private:
    Callbacks(const Callbacks &) = delete;
    Callbacks(Callbacks &&) = delete;
    Callbacks &operator=(const Callbacks &) = delete;
    Callbacks &operator=(Callbacks &&) = delete;
};

class PluginInterface {

public:
    virtual QString OnLoad(QDir &) = 0;
    virtual void OnAttach(const QHash<QString, PluginInterface *> &plugins, Callbacks *callbacks) = 0;
    virtual void OnUnload() = 0;

public:
    virtual ~PluginInterface() = default;

protected:
    PluginInterface() = default;

private:
    PluginInterface(const PluginInterface &) = delete;
    PluginInterface(PluginInterface &&) = delete;
    PluginInterface &operator=(const PluginInterface &) = delete;
    PluginInterface &operator=(PluginInterface &&) = delete;
};

} // namespace Plugin

Q_DECLARE_INTERFACE(Plugin::PluginInterface, PluginInterface_iid)

#endif // ifndef PLUGIN_BASE_H
