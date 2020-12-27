#include "ui_config_text_edit.h"

#include "../../settings.h"

namespace Ui {

void Ui_ConfigTextEdit::SetupUi(QTextEdit *w) {
    w->setWindowTitle(kPluginName);
}

} // namespace Ui
