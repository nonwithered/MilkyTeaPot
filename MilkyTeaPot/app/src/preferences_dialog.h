#ifndef PREFERENCES_DIALOG_H
#define PREFERENCES_DIALOG_H

#include <QDialog>

#include "ui/ui_preferences_dialog.h"

class PreferencesDialog : public QDialog {
    Q_OBJECT

public:
    ~PreferencesDialog();
    PreferencesDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    Ui::Ui_PreferencesDialog ui;

};

#endif // PREFERENCES_DIALOG_H
