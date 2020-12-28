#ifndef UI_PREFERENCE_EDITER_H
#define UI_PREFERENCE_EDITER_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {

class Ui_PreferenceEditor {

public:
    ~Ui_PreferenceEditor() = default;
    Ui_PreferenceEditor();

public:
    void SetupUi(QWidget *);

public:
    QSpinBox *position_x;
    QSpinBox *position_y;
    QSpinBox *width;
    QSpinBox *height;
    QComboBox *font_family;
    QSpinBox *font_size;
    QCheckBox *show_editor;
    QPushButton *apply;

private:
    Ui_PreferenceEditor(const Ui_PreferenceEditor &) = delete;
    Ui_PreferenceEditor(Ui_PreferenceEditor &&) = delete;
    Ui_PreferenceEditor &operator=(const Ui_PreferenceEditor &) = delete;
    Ui_PreferenceEditor &operator=(Ui_PreferenceEditor &&) = delete;

};

} // namespace Ui

#endif // UI_PREFERENCE_EDITER_H
