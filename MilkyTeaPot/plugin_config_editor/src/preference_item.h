#ifndef PREFERENCE_ITEM_H
#define PREFERENCE_ITEM_H

#include <QObject>
#include <QJsonObject>

class PreferenceItem : public QObject {
    Q_OBJECT

public:
    static PreferenceItem &Instance(QObject *parent = nullptr);

public:
    virtual ~PreferenceItem();

private:
    PreferenceItem(QObject *parent = nullptr);

public:
    void FromJson(QJsonObject);
    QJsonObject ToJson();

public:
    bool show_editor;
    QString font_family;
    int font_size;
    int width;
    int height;
    int position_x;
    int position_y;

private:
    PreferenceItem(const PreferenceItem &) = delete;
    PreferenceItem(PreferenceItem &&) = delete;
    PreferenceItem &operator=(const PreferenceItem &) = delete;
    PreferenceItem &operator=(PreferenceItem &&) = delete;

};

#endif // PREFERENCE_ITEM_H
