#include "ui_preferences_dialog.h"

#include <QHBoxLayout>

#include "../../settings.h"

namespace Ui {

void Ui_PreferencesDialog::SetupUi(QDialog *dialog) {
    QMetaObject::connectSlotsByName(dialog);
    dialog->setWindowTitle(QString::fromUtf8(kPluginsPreferences));
    list_widget = new QListWidget;
    stacked_layout = new QStackedLayout;
    QHBoxLayout *layout = new QHBoxLayout(dialog);
    layout->addWidget(list_widget);
    layout->addLayout(stacked_layout);
}

} // namespace Ui
