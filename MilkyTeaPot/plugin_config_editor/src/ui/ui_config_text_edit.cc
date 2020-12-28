#include "ui_config_text_edit.h"

#include <QWidget>
#include <QEvent>
#include <QMoveEvent>
#include <QResizeEvent>

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
    w->installEventFilter(&mdi_event_filter_);
}

bool MdiEventFilter::eventFilter(QObject *watched, QEvent *event) {
    QMdiSubWindow *sub_window = dynamic_cast<QMdiSubWindow *>(watched);
    if (sub_window == nullptr) {
        return false;
    }
    switch (event->type()) {
    case QEvent::Resize: {
        QSize size = sub_window->size();
        PreferenceItem::Instance().width = size.width();
        PreferenceItem::Instance().height = size.height();
        break;
    }
    case QEvent::Move: {
        QPoint pos = sub_window->pos();
        PreferenceItem::Instance().position_x = pos.x();
        PreferenceItem::Instance().position_y = pos.y();
        break;
    }
    default:
        break;
    }
    return false;
}

} // namespace Ui
