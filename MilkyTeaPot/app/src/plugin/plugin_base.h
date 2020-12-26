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

#include <functional>

#include "../../settings.h"

#define kInterfaceName "BasePlugin"
#define kInterfaceVersion "1.0"
#define AbstractPlugin_iid kAppName "." kInterfaceName "/" kInterfaceVersion

namespace Plugin {

class Callbacks : public QObject {
    Q_OBJECT

signals:
    void SignalNew();
    void SignalOpen(QFile &);
    void SignalSave(QFile &);
    void SignalClose();

public:
    virtual void SetModified() = 0;
    virtual void AddViewAction(QAction *action, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddViewMenu(QMenu *menu, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddViewSeparator(QAction *insert_before = nullptr) = 0;
    virtual void AddToolsAction(QAction *action, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddToolsMenu(QMenu *menu, QAction *insert_before = nullptr) = 0;
    virtual QAction *AddToolsSeparator(QAction *insert_before = nullptr) = 0;
    virtual void AddPreferencesOption(std::function<const QString(QWidget &)> option) = 0;
    virtual QMdiSubWindow *AddCentralSubWindow(QWidget *w) = 0;

public:
    Callbacks(QObject *parent = nullptr);
    ~Callbacks() override;

private:
    Callbacks(const Callbacks &) = delete;
    Callbacks(Callbacks &&) = delete;
    Callbacks &operator=(const Callbacks &) = delete;
    Callbacks &operator=(Callbacks &&) = delete;
};

class AbstractPlugin {

public:
    virtual QString OnLoad(QDir &) = 0;
    virtual void OnAttach(QHash<QString, AbstractPlugin *> &, Callbacks *) = 0;
    virtual void OnUnload() = 0;

public:
    AbstractPlugin() = default;
    virtual ~AbstractPlugin() = default;

private:
    AbstractPlugin(const AbstractPlugin &) = delete;
    AbstractPlugin(AbstractPlugin &&) = delete;
    AbstractPlugin &operator=(const AbstractPlugin &) = delete;
    AbstractPlugin &operator=(AbstractPlugin &&) = delete;
};

} // namespace Plugin

Q_DECLARE_INTERFACE(Plugin::AbstractPlugin, AbstractPlugin_iid)

#endif // ifndef PLUGIN_BASE_H
