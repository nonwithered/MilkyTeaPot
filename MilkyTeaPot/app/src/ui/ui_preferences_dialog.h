#ifndef UI_PREFERENCES_DIALOG_H
#define UI_PREFERENCES_DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedLayout>

namespace Ui {

class Ui_PreferencesDialog {

public:
    void SetupUi(QDialog *);

public:
    QListWidget *list_widget;
    QStackedLayout *stacked_layout;
};

} // namespace Ui

#endif // UI_PREFERENCES_DIALOG_H
