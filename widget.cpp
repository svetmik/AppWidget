#include "widget.h"



Widget::Widget(QWidget *parent)
    : ui::uiWidget{parent}

{

    fontWeight = this->font();
    fontWeight.setWeight(QFont::Weight::Normal);

    h_controlLayout = new QHBoxLayout(this); // main layout;
    h_controlLayout->setContentsMargins(0,0,0,0);

    _leftPanel = new Container(this);
    if(_leftPanel) {
        _leftPanel->setFixedSize(70, maximumHeight());
    }
    _leftPanel->setStyleSheet("background-color: #3b4353;");

    _menuButton = new Button("☰ Меню", _leftPanel);
    if(_menuButton) {
        _menuButton->resize(_leftPanel->width(), _menuButton->height() + 15);
        _menuButton->setFont(fontWeight);
    }
    _menuButton->setBackgroundColor(QColor(59,67,83));
    _menuButton->setHoverBackgroundColor(QColor(83,94,116));

    v_controlLayoutSidebar = new QVBoxLayout();
    v_controlLayoutSidebar->addWidget(_leftPanel);

    // layout для TextEdit, btnsend, btnAttchment, btnClose
    v_controlLayoutMain= new QVBoxLayout(this);
    v_controlLayoutMain->setContentsMargins(QMargins(0,6,5,5));

    _edit = new TextEdit(this);
    _edit->setPlaceholderText("Описание");

    _submitButton = new Button("Отправить заявку в ИТ-отдел");
    _attachButton = new Button("Прикрепить файл");
    _exitAppButton = new Button("Закрыть программу");


    v_controlLayoutMain->addWidget(_edit);
    v_controlLayoutMain->addWidget(_submitButton);
    v_controlLayoutMain->addWidget(_attachButton);
    v_controlLayoutMain->addWidget(_exitAppButton);


    h_controlLayout->addLayout(v_controlLayoutSidebar);
    h_controlLayout->addLayout(v_controlLayoutMain);

    // Боковая панель
    _sidebar = new sidebar(this);

    // overlay shadow
    _overlay = new overlay(this);

    this->controller = new FileController(this);
    controller->controllerSelectFile(_attachButton);

    overlay_box = new OverlayBox(this);

    QObject::connect(_menuButton, &Button::clicked, this, &Widget::hookToggle);
    QObject::connect(_submitButton, &Button::clicked, this, &Widget::sendFileToMail);

    QObject::connect(controller, &FileController::showModuleBox, this, [=]() {

        overlay_box->bodyText("Размер файла превышает 25 МБ");

        overlay_box->show();
    });


    QObject::connect(controller, &FileController::showModuleBoxEmptyFile, this, [=]() {

        overlay_box->bodyText("Файл не выбран");

        overlay_box->show();
    });


    QObject::connect(controller, &FileController::successSendMail, this, [=]() {

        overlay_box->bodyText("Заявка в IT-отдел отправлена");

        overlay_box->show();
    });
}

Widget::~Widget() = default;

void Widget::connectController() {



}
void Widget::hookToggle()
{
    if(_sidebar) {
        _sidebar->updateState();
    }
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

    MimeText text(_edit->toPlainText()); // Текст сообщени

    const auto mimeFile = this->controller->file_attachment();

    QFile addAttachement(mimeFile);
    QFile ZipFile("file.zip");

    MimeAttachment mime(&ZipFile);
    mime.setContentType("zip");
    MimeAttachment mime_1(&addAttachement);

    if(!mimeFile.isEmpty())
    {
        message.addPart(&text);  // описание заявки
        message.addPart(&mime);  // zip архив с вложенным скриншотом экрана.
        message.addPart(&mime_1); //  прикрепленный файл

    }  else if(mimeFile.isEmpty()) {
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

        emit controller->successSendMail();
        //очистка поля ввода текста QTextEdit
        this->_edit->clear();

        if(!controller->file_attachment().isEmpty()) {

            controller->clearFile();
        }
    }

    smtp.quit();

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


void Widget::mousePressEvent(QMouseEvent *event) {

}

void Widget::hideEvent(QHideEvent *event) {


}

void Widget::paintEvent(QPaintEvent *event) {

    QPainter p(this);
}

void Widget::resizeEvent(QResizeEvent *event) {

    if (_sidebar) {
        _sidebar->setGeometry(QRect(QPoint(_sidebar->pos()), QSize(this->size())));
    }


    if(_overlay) {
        _overlay->setGeometry(rect());
    }

    overlay_box->resize(event->size().width(), event->size().height());
}
