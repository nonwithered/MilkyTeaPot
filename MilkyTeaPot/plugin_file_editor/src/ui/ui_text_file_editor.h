#ifndef UI_TEXT_FILE_EDITOR_H
#define UI_TEXT_FILE_EDITOR_H

#include <QWidget>

namespace Ui {

class Ui_TextFileEditor {

public:
    ~Ui_TextFileEditor() = default;
    Ui_TextFileEditor() = default;

private:
    Ui_TextFileEditor(const Ui_TextFileEditor &) = delete;
    Ui_TextFileEditor(Ui_TextFileEditor &&) = delete;
    Ui_TextFileEditor &operator=(const Ui_TextFileEditor &) = delete;
    Ui_TextFileEditor &operator=(Ui_TextFileEditor &&) = delete;

public:
    void SetupUi(QWidget *);
};

} // namespace Ui

#endif // UI_TEXT_FILE_EDITOR_H
