#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QObject>
#include <QFile>

class ConfigManager : public QObject {
    Q_OBJECT

public:
    static ConfigManager &Instance(QObject* parent = nullptr);

public slots:
    void New();
    void Open(QFile &);
    void Save(QFile &);
    void Close();

public:
    ~ConfigManager();

private:
    ConfigManager(QObject* parent);

public:
    bool TryApply(const QString &);

private:
    ConfigManager(const ConfigManager &) = delete;
    ConfigManager(ConfigManager &&) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;
    ConfigManager &operator=(ConfigManager &&) = delete;

};

#endif // CONFIG_MANAGER_H
