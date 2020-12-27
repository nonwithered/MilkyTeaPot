#ifndef UI_CONFIG_TEXT_EDIT_H
#define UI_CONFIG_TEXT_EDIT_H

#include <QTextEdit>

namespace Ui {

class Ui_ConfigTextEdit {

public:
    ~Ui_ConfigTextEdit() = default;
    Ui_ConfigTextEdit() = default;

private:
    Ui_ConfigTextEdit(const Ui_ConfigTextEdit &) = delete;
    Ui_ConfigTextEdit(Ui_ConfigTextEdit &&) = delete;
    Ui_ConfigTextEdit &operator=(const Ui_ConfigTextEdit &) = delete;
    Ui_ConfigTextEdit &operator=(Ui_ConfigTextEdit &&) = delete;

public:
    void SetupUi(QTextEdit *);
};

} // namespace Ui

#endif // UI_CONFIG_TEXT_EDIT_H
