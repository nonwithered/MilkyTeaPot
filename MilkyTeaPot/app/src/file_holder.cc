#include "file_holder.h"

#include <QFile>
#include <QIODevice>

#include "plugin/plugin_manager.h"

FileHolder::~FileHolder() {
}

FileHolder::FileHolder(QObject *parent)
    : QObject(parent)
    , file_name_() {

}

bool FileHolder::Available() {
    return !file_name_.isEmpty();
}

void FileHolder::New() {
    Close();
    emit Plugin::Manager::Instance().SignalNew();
}

bool FileHolder::Open(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    emit Plugin::Manager::Instance().SignalOpen(file);
    file.close();
    return true;
}

bool FileHolder::Save() {
    return Save(file_name_);
}

bool FileHolder::SaveAs(QString file_name) {
    return Save(file_name);
}

void FileHolder::Close() {
    file_name_ = QString();
    emit Plugin::Manager::Instance().SignalClose();
}


bool FileHolder::Save(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }
    emit Plugin::Manager::Instance().SignalSave(file);
    file.close();
    file_name_ = file_name;
    return true;
}
