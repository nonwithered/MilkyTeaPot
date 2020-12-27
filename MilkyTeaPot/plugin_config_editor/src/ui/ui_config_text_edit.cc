#include "ui_config_text_edit.h"

#include <QWidget>

#include "../../settings.h"
#include "../preference_item.h"

namespace Ui {

void Ui_ConfigTextEdit::SetupUi(QTextEdit *w) {
    w->setWindowTitle(kPluginName);
    w->setWindowTitle("[*]" kPluginName);
    w->setFont(QFont(PreferenceItem::Instance().font_family, PreferenceItem::Instance().font_size));

    QMetaObject::connectSlotsByName(w);
}

void Ui_ConfigTextEdit::SetupMdi(QMdiSubWindow *w) {
    w->setWindowFlags(w->windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    w->resize(PreferenceItem::Instance().width, PreferenceItem::Instance().height);
    w->move(PreferenceItem::Instance().position_x, PreferenceItem::Instance().position_y);
}

} // namespace Ui
