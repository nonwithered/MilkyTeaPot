#include "file_manager.h"

#include <QFile>
#include <QIODevice>

#include "plugin/plugin_manager.h"

FileManager::~FileManager() {
}

FileManager::FileManager(QObject *parent)
    : QObject(parent)
    , file_name_() {

}

bool FileManager::Available() {
    return !file_name_.isEmpty();
}

void FileManager::New() {
    Close();
    emit Plugin::Manager::Instance().SignalNew();
}

bool FileManager::Open(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    emit Plugin::Manager::Instance().SignalOpen(file);
    file.close();
    return true;
}

bool FileManager::Save() {
    return Save(file_name_);
}

bool FileManager::SaveAs(QString file_name) {
    return Save(file_name);
}

void FileManager::Close() {
    file_name_ = QString();
    emit Plugin::Manager::Instance().SignalClose();
}


bool FileManager::Save(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }
    emit Plugin::Manager::Instance().SignalSave(file);
    file.close();
    file_name_ = file_name;
    return true;
}
