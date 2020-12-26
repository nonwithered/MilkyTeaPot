#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QObject>
#include <QString>

class FileManager : public QObject {
    Q_OBJECT

public:
    ~FileManager();
    FileManager(QObject *parent = nullptr);
    bool Available();
    void New();
    bool Open(QString file_name);
    bool Save();
    bool SaveAs(QString file_name);
    void Close();

private:
    bool Save(QString file_name);

private:
    QString file_name_;

private:
    FileManager(const FileManager &) = delete;
    FileManager(FileManager &&) = delete;
    FileManager &operator=(const FileManager &) = delete;
    FileManager &operator=(FileManager &&) = delete;
};

#endif // FILE_MANAGER_H
