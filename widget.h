#ifndef WIDGET_H
#define WIDGET_H

#include "UI/widgets/basewidget.h"

#include "global_objects.h"
#include "textedit.h"
#include "systeminfo.h"
#include "container.h"

#include "zipwriter_p.h"
#include "header/SmtpMime"

class Widget : public ui::uiWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // mail send;
    Button *_submitButton;

    // attch file;
    Button *_attachButton;

    // exit App;
    Button *_exitAppButton;

    // open sidebar Panel;
    Button *_menuButton;

    QHBoxLayout *h_controlLayout;
    QVBoxLayout *v_controlLayoutSidebar;
    QVBoxLayout *v_controlLayoutMain;

    //
    Container *_leftPanel;

    TextEdit *_edit;


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
    void hookToggle();

    // func for QObject connect slot
    void openFileDialog();

    // func for QObject connect slot
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
