#ifndef WIDGET_H
#define WIDGET_H

#include "UI/widgets/basewidget.h"

#include "global_objects.h"
#include "left_bar.h"
#include "textedit.h"
#include "systeminfo.h"
#include "zipwriter_p.h"
#include "header/SmtpMime"

class Widget : public ui::uiWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Button *btnSend;
    Button *btnAttachment;
    Button *btnClose;
    Button *btnOpenSideBar;

    QHBoxLayout *h_controlLayout;
    QVBoxLayout *v_controlLayoutSidebar;
    QVBoxLayout *v_controlLayoutMain;


    TextEdit *edit;
    left_bar *leftBar;

    // get screen_data from monitor
    QByteArray getScreenshotApp(int screen, const char *format, int quality = -1);

    // write screen_data to zip arhive
    void writetoFile(const char *path, const char *name, QByteArray &data);

protected:

    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    // infomation ip-pc, domainName, printerName
    SystemInfo pc;

    // state left sidebar ON || OFF
    void toggle();

    // QObject connect slot
    void openFileDialog();

    //QObject connect slot
    void closeWindowApp(QMainWindow &handleEvent);

    // QObject connect slot
    void sendFileToMail();

    // create zip arhive
    int zipFileAttachement(const char *FileNamePicture, const char *ZipFileName, QByteArray &data);

    // var get FilePath Dialog
    QString m_filePath{};

    // ;
    bool setfilePathDialog(const QString &filePath);

    // get
    QString getfilePathDialog() const;

};
#endif // WIDGET_H
