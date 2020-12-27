#ifndef CONFIG_TEXT_EDIT_H
#define CONFIG_TEXT_EDIT_H

#include <QTextEdit>

#include "ui/ui_config_text_edit.h"

class ConfigTextEdit : public QTextEdit {
    Q_OBJECT

public:
    ~ConfigTextEdit();
    ConfigTextEdit(QWidget* parent = nullptr);

private:
    Ui::Ui_ConfigTextEdit ui;

private:
    ConfigTextEdit(const ConfigTextEdit &) = delete;
    ConfigTextEdit(ConfigTextEdit &&) = delete;
    ConfigTextEdit &operator=(const ConfigTextEdit &) = delete;
    ConfigTextEdit &operator=(ConfigTextEdit &&) = delete;
};

#endif // CONFIG_TEXT_EDIT_H
