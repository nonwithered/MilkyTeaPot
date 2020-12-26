#ifndef TEXT_FILE_EDITOR_H
#define TEXT_FILE_EDITOR_H

#include <QWidget>

#include "ui/ui_text_file_editor.h"

class TextFileEditor : public QWidget {
    Q_OBJECT

public:
    ~TextFileEditor();
    TextFileEditor(QWidget* parent = nullptr);

private:
    Ui::Ui_TextFileEditor ui;

private:
    TextFileEditor(const TextFileEditor &) = delete;
    TextFileEditor(TextFileEditor &&) = delete;
    TextFileEditor &operator=(const TextFileEditor &) = delete;
    TextFileEditor &operator=(TextFileEditor &&) = delete;
};

#endif // TEXT_FILE_EDITOR_H
