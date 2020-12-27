#include "config_manager.h"

ConfigManager &ConfigManager::Instance(QObject* parent) {
    static ConfigManager *instance = new ConfigManager(parent);
    return *instance;
}

void ConfigManager::New() {
}

void ConfigManager::Open(QFile &) {
}

void ConfigManager::Save(QFile &) {
}

void ConfigManager::Close() {
}

ConfigManager::~ConfigManager() {
}

ConfigManager::ConfigManager(QObject* parent)
    : QObject(parent) {
}

bool ConfigManager::TryApply(const QString &) {
    return false;
}
