#include "ui_preference_editer.h"

#include <QApplication>
#include <QScreen>
#include <QRect>
#include <QGridLayout>
#include <QLabel>
#include <QFontDatabase>

#include "../../settings.h"
#include "../preference_item.h"

namespace Ui {

Ui_PreferenceEditor::Ui_PreferenceEditor() {
    position_x = new QSpinBox;
    position_y = new QSpinBox;
    width = new QSpinBox;
    height = new QSpinBox;
    font_family = new QComboBox;
    foreach (const QString &f, QFontDatabase().families()) {
        font_family->addItem(f);
    }
    font_size = new QSpinBox;
    show_editor = new QCheckBox(KEY_OF(show_editor));
    apply = new QPushButton(QString::fromUtf8("apply"));
}

void Ui_PreferenceEditor::SetupUi(QWidget *w) {
    QGridLayout *layout = new QGridLayout(w);
    layout->addWidget(new QLabel(KEY_OF(position_x)), 0, 0);
    layout->addWidget(position_x, 1, 0);
    layout->addWidget(new QLabel(KEY_OF(position_y)), 0, 1);
    layout->addWidget(position_y, 1, 1);
    layout->addWidget(new QLabel(KEY_OF(width)), 0, 2);
    layout->addWidget(width, 1, 2);
    layout->addWidget(new QLabel(KEY_OF(height)), 0, 3);
    layout->addWidget(height, 1, 3);
    layout->addWidget(new QLabel(KEY_OF(font_family)), 2, 0);
    layout->addWidget(font_family, 3, 0);
    layout->addWidget(new QLabel(KEY_OF(font_size)), 2, 1);
    layout->addWidget(font_size, 3, 1);
    layout->addWidget(new QLabel(KEY_OF(show_editor)), 2, 2);
    layout->addWidget(show_editor, 3, 2);
    layout->addWidget(apply, 3, 3);
    QMetaObject::connectSlotsByName(w);
}

} // namespace Ui
