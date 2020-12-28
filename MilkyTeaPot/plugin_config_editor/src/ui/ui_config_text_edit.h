#ifndef UI_CONFIG_TEXT_EDIT_H
#define UI_CONFIG_TEXT_EDIT_H

#include <QTextEdit>
#include <QMdiSubWindow>

namespace Ui {

class MdiEventFilter : public QObject {
    Q_OBJECT

public:
    bool eventFilter(QObject *watched, QEvent *event) final;
};

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
    void SetupMdi(QMdiSubWindow *);

private:
     MdiEventFilter mdi_event_filter_;
};

} // namespace Ui

#endif // UI_CONFIG_TEXT_EDIT_H
