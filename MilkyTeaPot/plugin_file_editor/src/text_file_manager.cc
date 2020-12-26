#include "text_file_manager.h"

TextFileManager &TextFileManager::Instance(QObject* parent) {
    static TextFileManager *instance = new TextFileManager(parent);
    return *instance;
}

void TextFileManager::New() {
}

void TextFileManager::Open(QFile &) {
}

void TextFileManager::Save(QFile &) {
}

void TextFileManager::Close() {
}

TextFileManager::~TextFileManager() {
}

TextFileManager::TextFileManager(QObject* parent)
    : QObject(parent) {
}
