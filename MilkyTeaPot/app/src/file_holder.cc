#include "file_holder.h"

#include <QFile>
#include <QIODevice>

FileHolder::FileHolder(QObject *parent)
    : QObject(parent)
    , file_name_()
    , bytes_() {

}

FileHolder::~FileHolder() {
}

bool FileHolder::Available() {
    return !file_name_.isEmpty();
}

void FileHolder::New() {
    Close();
}

bool FileHolder::Open(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    bytes_ = file.readAll();
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
    bytes_.clear();
}


bool FileHolder::Save(QString file_name) {
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(bytes_);
    file.close();
    return true;
}
