#include "filecontroller.h"

FileController::FileController(QObject *parent)
    : QObject{parent}
{
}

void FileController::controllerSelectFile(Button *btn)
{

    QObject::connect(btn, &Button::clicked, this, [this, btn]()
                     { this->filePath(btn); });

    QObject::connect(this, &FileController::checkCleared, this, [this, btn]()
                     { btn->setText("Прикрепить файл"); });

    QObject::connect(this, &FileController::selectFile, this, [this, btn]()
                     { btn->setText("Файл успешно прикреплён"); });
}

void FileController::filePath(Button *btn)
{

    QString dirDestopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    dirDestopPath = QDir::toNativeSeparators(dirDestopPath);

    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        tr("Выбрать файл"),
        dirDestopPath,
        "All files (*);; Archives (*.zip *.rar)");

    if (filePath.isEmpty())
    {
        clearFile();
        emit showModuleBoxEmptyFile();

        return;
    }

    if (checkFileSize(filePath))
    {

        this->m_filePath = filePath;

        emit selectFile(m_filePath);

    } else if (!checkFileSize(filePath))
    {

        clearFile();

        emit showModuleBox();

    } 
}

const QString &FileController::file_attachment() const
{
    return m_filePath;
}

void FileController::clearFile()
{

    m_filePath.clear();

    emit checkCleared();
}

bool FileController::checkFileSize(const QString &filePath)
{
    // 25 мбайт максимальный размер файла
    qint64 maxSize = 25 * 1024 * 1024;

    QFileInfo info{filePath};

    if (info.exists() and info.size() <= maxSize)
    {
        return true;
    }

    return false;
}
