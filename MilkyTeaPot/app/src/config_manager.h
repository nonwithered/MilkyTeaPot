#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class ConfigManager : public QObject {
    Q_OBJECT

public:
    ~ConfigManager();
    ConfigManager(QObject *parent = nullptr);
    QJsonObject &GetConfig();
    bool Available();
    void New();
    bool Open(QString file_name);
    bool Save();
    bool SaveAs(QString file_name);
    void Close();

private:
    bool Save(QString file_name);
    void NewConfig();

private:
    QString file_name_;
    QJsonObject config_;

private:
    ConfigManager(const ConfigManager &) = delete;
    ConfigManager(ConfigManager &&) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;
    ConfigManager &operator=(ConfigManager &&) = delete;
};

#endif // CONFIG_MANAGER_H
