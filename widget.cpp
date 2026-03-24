#include "widget.h"



Widget::Widget(QWidget *parent)
    : ui::uiWidget{parent}

{

    h_controlLayout = new QHBoxLayout(this); // main layout;
    h_controlLayout->setContentsMargins(0,0,0,0);

    leftBar = new left_bar(this);

    btnOpenSideBar = new Button("☰ Меню", leftBar);
    btnOpenSideBar->resize(leftBar->width(), btnOpenSideBar->height() + 15);
    btnOpenSideBar->setBackgroundColor(QColor(59,67,83));
    btnOpenSideBar->setHoverBackgroundColor(QColor(83,94,116));

    v_controlLayoutSidebar = new QVBoxLayout(); // layout для TextEdit, btnsend, btnAttchment, btnClose
    v_controlLayoutSidebar->addWidget(leftBar);

    v_controlLayoutMain= new QVBoxLayout(this);
    v_controlLayoutMain->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    v_controlLayoutMain->setContentsMargins(0,5,5,5);

    edit = new TextEdit(this);
    edit->setPlaceholderText("Описание");

    btnSend = new Button("Отправить заявку в ИТ-отдел");
    btnSend->setBorderRadius(3,3);

    btnAttachment = new Button("Прикрепить файл");
    btnAttachment->setBorderRadius(3,3);

    btnClose = new Button("Закрыть программу");
    btnClose->setBorderRadius(3,3);

    v_controlLayoutMain->addWidget(edit);
    v_controlLayoutMain->addWidget(btnSend);
    v_controlLayoutMain->addWidget(btnAttachment);
    v_controlLayoutMain->addWidget(btnClose);


    h_controlLayout->addLayout(v_controlLayoutSidebar);
    h_controlLayout->addLayout(v_controlLayoutMain);


    _sidebar = new sidebar(this);
    _sidebar->setGeometry(_sidebar->x(), _sidebar->y(), _sidebar->width(), this->height());

    _overlay = new overlay(this);
    _overlay->hide();

    QObject::connect(btnOpenSideBar, &Button::clicked, this, &Widget::toggle);
    QObject::connect(btnAttachment, &Button::clicked, this, &Widget::openFileDialog);
    QObject::connect(btnSend, &Button::clicked, this, &Widget::sendFileToMail);
}

Widget::~Widget()
{

}


void Widget::toggle()
{
    _sidebar->raise(); // перемещаем виджет на передний план;

    _sidebar->updateState();

}

void Widget::sendFileToMail() {

    MimeMessage message;

    // почта, с которой будут рассылаться заявки .. admin.domain и тд
    EmailAddress sender("ivan-svet@mail.ru", "Заявка в ИТ-отдел");
    message.setSender(sender);

    // почта, на которую будут переадресация заявок
    EmailAddress to("ivan-svet@mail.ru", "Recipient's Name");
    message.addRecipient(to);

    QString subject = _sidebar->pcInfo->localIpAddressPc() + " | " +
                      _sidebar->pcInfo->localHostName() + " | " +
                      _sidebar->pcInfo->localPrinterName();

    message.setSubject(subject); // Тема сообщения

    MimeText text(edit->toPlainText()); // Текст сообщени

    QFile addAttachement(getfilePathDialog());
    QFile ZipFile("file.zip");

    MimeAttachment mime(&ZipFile);
    mime.setContentType("zip");
    MimeAttachment mime_1(&addAttachement);

    if(!getfilePathDialog().isEmpty())
    {
        message.addPart(&text);  // описание заявки
        message.addPart(&mime);  // zip архив с вложенным скриншотом экрана.
        message.addPart(&mime_1); //  прикрепленный файл

    }  else if(getfilePathDialog().isEmpty()) {
        message.addPart(&text);
        message.addPart(&mime);
    }


    SmtpClient smtp("smtp.mail.ru", 465, SmtpClient::SslConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        //errorMessage("Failed to connect host");
        return;
    }

    // login
    // указать почту, в который был создан приватный ключ, для внешних приложений
    // указать сам приватный ключ
    smtp.login("ivan-svet@mail.ru", "D17FAOL2bYSkXSbbaP5A");
    if (!smtp.waitForAuthenticated()) {
        //errorMessage("Failed to login!");
        return;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
        //errorMessage("Failed to send mail!");
        return;
    } else {
        //очистка поля ввода текста
        this->edit->clear();
    }



}

QByteArray Widget::getScreenshotApp(int screen, const char *format, int quality) {

    QByteArray screenshot_data;

    QScreen *sn = qApp->screens().at(screen); //create shreenshot

    QPixmap pixmap = sn->grabWindow(0);

    QBuffer buf{&screenshot_data};

    buf.open(QIODevice::WriteOnly);

    pixmap.save(&buf,format,quality);

    return screenshot_data;
}

int Widget::zipFileAttachement(const char *FileNamePicture, const char *ZipFileName, QByteArray &data) {

    QZipWriter *zip = new QZipWriter(ZipFileName, QIODevice::WriteOnly); // создаем архим

    if(zip->status() == QZipWriter::NoError)
    {
        zip->addFile(FileNamePicture, data); // добавляется файл в zip.архив ---> Наименнование.png | файл

        zip->setCompressionPolicy(QZipWriter::AlwaysCompress); // сжатие файла

        zip->close();

    }
    return 0;
}

void Widget::writetoFile(const char *path, const char *name, QByteArray &data) {

    QString file_path(path);

    if(!file_path.endsWith('/'))
    {
        file_path += '/';
    }

    file_path.append(name);

    QFile file(file_path);

    file.open(QIODevice::WriteOnly);

    file.write(data);

    zipFileAttachement("screenshot.png","file.zip", data);

    file.waitForBytesWritten(1000);
}

bool Widget::setfilePathDialog(const QString &filePath) {

    // 25 мбайт максимальный размер файла
    qint64 maxSize = 25 * 1024 * 1024;

    QFileInfo info{filePath};

    if(info.exists() and info.size() <= maxSize) {
        this->m_filePath = filePath;

        return true;

    }

    return false;
}


QString Widget::getfilePathDialog() const {

    return this->m_filePath;
}

void Widget::openFileDialog() {

    // Desktop Path
    QString dirDestopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    dirDestopPath = QDir::toNativeSeparators(dirDestopPath);

    QString filePath = QFileDialog::getOpenFileName(

        this,
        tr("Выбрать файл"),
        dirDestopPath,
        "All files (*);; Archives (*.zip *.rar)"
        );

    if(setfilePathDialog(filePath)) {
        qDebug() << "успешно";
    } else {
        qDebug() << "что то пошло не так";
    }
}

void Widget::closeWindowApp(QMainWindow &handleEvent) {

    handleEvent.close();
}


void Widget::mousePressEvent(QMouseEvent *event) {

}

void Widget::hideEvent(QHideEvent *event) {


}

void Widget::paintEvent(QPaintEvent *event) {

    QPainter p(this);
}

void Widget::resizeEvent(QResizeEvent *event) {


    if (_sidebar) {
        _sidebar->setGeometry(_sidebar->x(), _sidebar->y(), _sidebar->width(), height()); // Занимаем весь родительский
        _sidebar->update(); // Принудительно перерисовать
    }


    if(_overlay) {
        _overlay->resize(event->size().width(), event->size().height());
    }
}
