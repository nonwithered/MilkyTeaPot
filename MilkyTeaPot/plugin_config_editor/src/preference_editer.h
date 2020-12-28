#ifndef PREFERENCE_EDITER_H
#define PREFERENCE_EDITER_H

#include <QWidget>

#include "ui/ui_preference_editer.h"

class PreferenceEditor : public QWidget {
    Q_OBJECT

public:
    virtual ~PreferenceEditor();
    PreferenceEditor(QWidget *parent = nullptr);

private slots:
    void Refresh();
    void Modify();

private:
    Ui::Ui_PreferenceEditor ui;

private:
    PreferenceEditor(const PreferenceEditor &) = delete;
    PreferenceEditor(PreferenceEditor &&) = delete;
    PreferenceEditor &operator=(const PreferenceEditor &) = delete;
    PreferenceEditor &operator=(PreferenceEditor &&) = delete;

};

#endif // PREFERENCE_EDITER_H
