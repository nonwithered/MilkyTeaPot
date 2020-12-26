#include "ui_preferences_dialog.h"

#include <QGridLayout>

#include "../../settings.h"

namespace Ui {

void Ui_PreferencesDialog::SetupUi(QDialog *dialog) {
    QMetaObject::connectSlotsByName(dialog);
    dialog->setWindowTitle(QString::fromUtf8(kPluginsPreferences));
    list_widget = new QListWidget;
    stacked_layout = new QStackedLayout;
    QGridLayout *grid_layout = new QGridLayout(dialog);
    grid_layout->addWidget(list_widget, 0, 0);
    grid_layout->addLayout(stacked_layout, 0, 1);
}

} // namespace Ui
