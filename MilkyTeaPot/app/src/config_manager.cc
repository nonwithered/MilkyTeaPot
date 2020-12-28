#include "config_manager.h"

#include <QFile>
#include <QIODevice>
#include <QJsonDocument>

#include "plugin/plugin_manager.h"

ConfigManager::~ConfigManager() {
}

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent)
    , file_name_() {
}

QJsonObject &ConfigManager::GetConfig() {
    return config_;
}

bool ConfigManager::Available() {
    return !file_name_.isEmpty();
}

void ConfigManager::New() {
    NewConfig();
    emit Plugin::Manager::Instance().SignalNew();
}

bool ConfigManager::Open(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isObject()) {
        return false;
    }
    file_name_ = file_name;
    config_ = doc.object();
    emit Plugin::Manager::Instance().SignalOpen(file);
    return true;
}

bool ConfigManager::Save() {
    return Save(file_name_);
}

bool ConfigManager::SaveAs(QString file_name) {
    return Save(file_name);
}

void ConfigManager::Close() {
    file_name_ = QString();
    config_ = QJsonObject();
    emit Plugin::Manager::Instance().SignalClose();
}

void ConfigManager::Quit() {
    emit Plugin::Manager::Instance().SignalQuit();
}

bool ConfigManager::Save(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QJsonDocument doc(config_);
    file.write(doc.toJson());
    emit Plugin::Manager::Instance().SignalSave(file);
    file.close();
    file_name_ = file_name;
    return true;
}

void ConfigManager::NewConfig() {
}
