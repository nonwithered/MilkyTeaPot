#include "preference_item.h"

#include <QScreen>
#include <QApplication>
#include <QFont>

#include "settings.h"

PreferenceItem &PreferenceItem::Instance(QObject *parent) {
    static PreferenceItem *instance = new PreferenceItem(parent);
    return *instance;
}

PreferenceItem::~PreferenceItem() {
}

PreferenceItem::PreferenceItem(QObject *parent)
    : QObject(parent) {
    show_editor = false;
    width = kDefaultWidth;
    height = kDefaultHeight;
    position_x = 0;
    position_y = 0;
    font_family = qApp->font().family();
    font_size = qApp->font().pointSize();
}

void PreferenceItem::Ensure() {
    QRect rect = QGuiApplication::screens().at(0)->availableGeometry();
    int w = rect.width();
    int h = rect.height();
    if (position_x < 0) {
        position_x = 0;
    } else if (position_x >= w) {
        position_x = w - 1;
    }
    if (position_y < 0) {
        position_y = 0;
    } else if (position_y >= h) {
        position_y = h - 1;
    }
    if (width < 1) {
        width = 1;
    } else if (width > w - position_x) {
        width = w - position_x;
    }
    if (height < 1) {
        height = 1;
    } else if (height > h - position_y) {
        height = h - position_y;
    }
    if (font_size < 1) {
        font_size = 1;
    } else if (font_size > kMaxFontSize) {
        font_size = kMaxFontSize;
    }
    emit Modified();
}

void PreferenceItem::FromJson(QJsonObject json) {
    QJsonValue v;
    v = json.value(KEY_OF(position_x));
    if (v.isDouble()) {
        position_x = v.toInt();
    }
    v = json.value(KEY_OF(position_y));
    if (v.isDouble()) {
        position_y = v.toInt();
    }
    v = json.value(KEY_OF(width));
    if (v.isDouble()) {
        width = v.toInt();
    }
    v = json.value(KEY_OF(height));
    if (v.isDouble()) {
        height = v.toInt();
    }
    v = json.value(KEY_OF(font_family));
    if (v.isString()) {
        font_family = v.toString();
    }
    v = json.value(KEY_OF(font_size));
    if (v.isDouble()) {
        font_size = v.toInt();
    }
    v = json.value(KEY_OF(show_editor));
    if (v.isBool()) {
        show_editor = v.toBool();
    }
    Ensure();
}

QJsonObject PreferenceItem::ToJson() {
    QJsonObject json;
    json.insert(KEY_OF(position_x), position_x);
    json.insert(KEY_OF(position_y), position_y);
    json.insert(KEY_OF(width), width);
    json.insert(KEY_OF(height), height);
    json.insert(KEY_OF(font_family), font_family);
    json.insert(KEY_OF(font_size), font_size);
    json.insert(KEY_OF(show_editor), show_editor);
    return json;
}
