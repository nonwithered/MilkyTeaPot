#ifndef PREFERENCE_ITEM_H
#define PREFERENCE_ITEM_H

#include <QObject>
#include <QJsonObject>

#define KEY_OF(k) QString::fromUtf8(#k)

class PreferenceItem : public QObject {
    Q_OBJECT

public:
    static PreferenceItem &Instance(QObject *parent = nullptr);

signals:
    void Modified();

public:
    virtual ~PreferenceItem();

private:
    PreferenceItem(QObject *parent = nullptr);

public:
    void Ensure();
    void FromJson(QJsonObject);
    QJsonObject ToJson();

public:
    int position_x;
    int position_y;
    int width;
    int height;
    QString font_family;
    int font_size;
    bool show_editor;

private:
    PreferenceItem(const PreferenceItem &) = delete;
    PreferenceItem(PreferenceItem &&) = delete;
    PreferenceItem &operator=(const PreferenceItem &) = delete;
    PreferenceItem &operator=(PreferenceItem &&) = delete;

};

#endif // PREFERENCE_ITEM_H
