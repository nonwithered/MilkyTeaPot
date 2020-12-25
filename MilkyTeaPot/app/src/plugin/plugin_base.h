#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#include <QString>
#include <QHash>
#include <QDir>

#include "../../settings.h"

#define kInterfaceName "BasePlugin"
#define kInterfaceVersion "1.0"
#define BasePlugin_iid kAppName "." kInterfaceName "/" kInterfaceVersion

namespace Plugin {

class BaseEvents : public QObject {
    Q_OBJECT

public:
    BaseEvents();
    ~BaseEvents();

private:
    BaseEvents(const BaseEvents &) = delete;
    BaseEvents(BaseEvents &&) = delete;
    BaseEvents &operator=(const BaseEvents &) = delete;
    BaseEvents &operator=(BaseEvents &&) = delete;
};

class BasePlugin {

public:
    virtual QString OnLoad(QDir &) = 0;
    virtual void OnAttach(QHash<QString, BasePlugin *> &, BaseEvents &) = 0;
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
