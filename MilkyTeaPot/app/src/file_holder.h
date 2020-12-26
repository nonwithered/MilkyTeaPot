#ifndef FILE_HOLDER_H
#define FILE_HOLDER_H

#include <QObject>
#include <QString>

class FileHolder : public QObject {
    Q_OBJECT

public:
    ~FileHolder();
    FileHolder(QObject *parent = nullptr);
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
    FileHolder(const FileHolder &) = delete;
    FileHolder(FileHolder &&) = delete;
    FileHolder &operator=(const FileHolder &) = delete;
    FileHolder &operator=(FileHolder &&) = delete;
};

#endif // FILE_HOLDER_H
