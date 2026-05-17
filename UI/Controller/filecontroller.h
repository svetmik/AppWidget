#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QObject>
#include <QFileDialog>

#include "../widgets/button.h"

class FileController : public QObject
{
    Q_OBJECT

public:

    explicit FileController(QObject *parent = nullptr);

    void controllerSelectFile(Button *btn);

    QString &file_attachment();

    void clearFile();

private slots:

    void filePath(Button *btn);

signals:

    void selectFile(const QString &filePath);

    void checkCleared();

private:

    QString m_filePath;

    bool checkFileSize(const QString &filePath);

};

#endif // FILECONTROLLER_H
