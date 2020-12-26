#ifndef TEXT_FILE_MANAGER_H
#define TEXT_FILE_MANAGER_H

#include <QObject>
#include <QFile>

class TextFileManager : public QObject {
    Q_OBJECT

public:
    static TextFileManager &Instance(QObject* parent = nullptr);

public slots:
    void New();
    void Open(QFile &);
    void Save(QFile &);
    void Close();

public:
    ~TextFileManager();

private:
    TextFileManager(QObject* parent);

private:
    TextFileManager(const TextFileManager &) = delete;
    TextFileManager(TextFileManager &&) = delete;
    TextFileManager &operator=(const TextFileManager &) = delete;
    TextFileManager &operator=(TextFileManager &&) = delete;

};

#endif // TEXT_FILE_MANAGER_H
