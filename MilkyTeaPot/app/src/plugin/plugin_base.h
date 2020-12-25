#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#include <QString>
#include <QHash>
#include <QDir>
#include <QFile>
#include <QAction>
#include <QMenu>

#include <functional>
#include <tuple>

#include "../../settings.h"

#define kInterfaceName "BasePlugin"
#define kInterfaceVersion "1.0"
#define BasePlugin_iid kAppName "." kInterfaceName "/" kInterfaceVersion

namespace Plugin {

class Callbacks : public QObject {
    Q_OBJECT

signals:
    void SignalNew();
    void SignalOpen(QFile &);
    void SignalSave(QFile &);
    void SignalClose();

public:
    void SetModified();
    void AddViewAction(QAction *action, QAction *insert_before = nullptr);
    QAction *AddViewMenu(QMenu *menu, QAction *insert_before = nullptr);
    QAction *AddViewSeparator(QAction *insert_before = nullptr);
    void AddToolsAction(QAction *action, QAction *insert_before = nullptr);
    QAction *AddToolsMenu(QMenu *menu, QAction *insert_before = nullptr);
    QAction *AddToolsSeparator(QAction *insert_before = nullptr);
    void AddPreferencesOption(std::function<std::tuple<const QString *, QWidget *>()> option);

public:
    Callbacks();
    ~Callbacks();

private:
    Callbacks(const Callbacks &) = delete;
    Callbacks(Callbacks &&) = delete;
    Callbacks &operator=(const Callbacks &) = delete;
    Callbacks &operator=(Callbacks &&) = delete;
};

class BasePlugin {

public:
    virtual QString OnLoad(QDir &) = 0;
    virtual void OnAttach(QHash<QString, BasePlugin *> &, Callbacks &) = 0;
    virtual void OnUnload() = 0;

public:
    BasePlugin() = default;

private:
    BasePlugin(const BasePlugin &) = delete;
    BasePlugin(BasePlugin &&) = delete;
    BasePlugin &operator=(const BasePlugin &) = delete;
    BasePlugin &operator=(BasePlugin &&) = delete;
};

} // namespace Plugin

Q_DECLARE_INTERFACE(Plugin::BasePlugin, BasePlugin_iid)

#endif // ifndef PLUGIN_BASE_H
