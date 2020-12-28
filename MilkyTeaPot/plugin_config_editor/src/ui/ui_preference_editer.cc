#include "ui_preference_editer.h"

#include <QApplication>
#include <QScreen>
#include <QRect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFontDatabase>

#include "../../settings.h"
#include "../preference_item.h"

namespace Ui {

Ui_PreferenceEditor::Ui_PreferenceEditor() {
    position_x = new QSpinBox;
    position_x->setRange(0, 9999);
    position_y = new QSpinBox;
    position_y->setRange(0, 9999);
    width = new QSpinBox;
    width->setRange(1, 9999);
    height = new QSpinBox;
    height->setRange(1, 9999);
    font_family = new QComboBox;
    foreach (const QString &f, QFontDatabase().families()) {
        font_family->addItem(f);
    }
    font_size = new QSpinBox;
    font_size->setRange(1, 99);
    show_editor = new QCheckBox(KEY_OF(show_editor));
    apply = new QPushButton(QString::fromUtf8("apply"));
}

void Ui_PreferenceEditor::SetupUi(QWidget *w) {
    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->addWidget(new QLabel(KEY_OF(position_x)), 0, 0);
    grid_layout->addWidget(position_x, 0, 1);
    grid_layout->addWidget(new QLabel(KEY_OF(position_y)), 1, 0);
    grid_layout->addWidget(position_y, 1, 1);
    grid_layout->addWidget(new QLabel(KEY_OF(width)), 2, 0);
    grid_layout->addWidget(width, 2, 1);
    grid_layout->addWidget(new QLabel(KEY_OF(height)), 3, 0);
    grid_layout->addWidget(height, 3, 1);
    grid_layout->addWidget(new QLabel(KEY_OF(font_family)), 0, 2);
    grid_layout->addWidget(font_family, 0, 3);
    grid_layout->addWidget(new QLabel(KEY_OF(font_size)), 1, 2);
    grid_layout->addWidget(font_size, 1, 3);
    grid_layout->addWidget(show_editor, 2, 3);
    QHBoxLayout *hbox_layout = new QHBoxLayout;
    hbox_layout->addStretch();
    hbox_layout->addWidget(apply);
    QVBoxLayout *vbox_layout = new QVBoxLayout(w);
    vbox_layout->addLayout(grid_layout);
    vbox_layout->addLayout(hbox_layout);
    QMetaObject::connectSlotsByName(w);
}

} // namespace Ui
