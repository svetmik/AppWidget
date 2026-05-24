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

    const QString &file_attachment() const ;

    void clearFile();

private slots:

    void filePath(Button *btn);

signals:

    void selectFile(const QString &filePath);

    void checkCleared();


    void showModuleBox();

    void showModuleBoxEmptyFile();

    void successSendMail();
private:

    QString m_filePath;

    bool checkFileSize(const QString &filePath);


};

#endif // FILECONTROLLER_H
