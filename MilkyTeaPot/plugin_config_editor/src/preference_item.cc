#include "preference_item.h"

#include <QApplication>
#include <QFont>

#include "settings.h"

#define KEY_SHOW_EDITOR "show_editor"
#define KEY_WIDTH "width"
#define KEY_HEIGHT "height"
#define KEY_POSITION_X "position_x"
#define KEY_POSITION_Y "position_y"
#define KEY_FONT_FAMILY "font_family"
#define KEY_FONT_SIZE "font_size"

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

void PreferenceItem::FromJson(QJsonObject json) {
    QJsonValue v;
    v = json.value(KEY_SHOW_EDITOR);
    if (v.isBool()) {
        show_editor = v.toBool();
    }
    v = json.value(KEY_WIDTH);
    if (v.isDouble()) {
        width = v.toInt();
    }
    v = json.value(KEY_HEIGHT);
    if (v.isDouble()) {
        height = v.toInt();
    }
    v = json.value(KEY_POSITION_X);
    if (v.isDouble()) {
        position_x = v.toInt();
    }
    v = json.value(KEY_POSITION_Y);
    if (v.isDouble()) {
        position_y = v.toInt();
    }
    v = json.value(KEY_FONT_FAMILY);
    if (v.isString()) {
        font_family = v.toString();
    }
    v = json.value(KEY_FONT_SIZE);
    if (v.isDouble()) {
        font_size = v.toInt();
    }
}

QJsonObject PreferenceItem::ToJson() {
    QJsonObject json;
    json.insert(KEY_SHOW_EDITOR, show_editor);
    json.insert(KEY_WIDTH, width);
    json.insert(KEY_HEIGHT, height);
    json.insert(KEY_POSITION_X, position_x);
    json.insert(KEY_POSITION_Y, position_y);
    json.insert(KEY_FONT_FAMILY, font_family);
    json.insert(KEY_FONT_SIZE, font_size);
    return json;
}
