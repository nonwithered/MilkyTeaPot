#ifndef UI_PREFERENCES_DIALOG_H
#define UI_PREFERENCES_DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedLayout>

namespace Ui {

class Ui_PreferencesDialog {

public:
    Ui_PreferencesDialog() = default;
    ~Ui_PreferencesDialog() = default;

private:
    Ui_PreferencesDialog(const Ui_PreferencesDialog &) = delete;
    Ui_PreferencesDialog(Ui_PreferencesDialog &&) = delete;
    Ui_PreferencesDialog &operator=(const Ui_PreferencesDialog &) = delete;
    Ui_PreferencesDialog &operator=(Ui_PreferencesDialog &&) = delete;

public:
    void SetupUi(QDialog *);

public:
    QListWidget *list_widget;
    QStackedLayout *stacked_layout;
};

} // namespace Ui

#endif // UI_PREFERENCES_DIALOG_H
