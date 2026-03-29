#include "sidebar.h"
#include "global_objects.h"



constexpr auto sidebarname = "siBarWidgetPanel";

sidebar::sidebar(QWidget *parent)
    : ui::uiWidget{parent}
{
    setAutoFillBackground(true);
    // Начальная позиция - скрыт за левым краем
    move(-230, 0);
    setFixedWidth(230);
    setMinimumHeight(300);
    setContentsMargins(0,0,0,0);
    setStyleSheet("background-color: white");

    // widget
    container = new Container;
    container->setContentsMargins(0,0,0,0);
    container->setMinimumHeight(200);
    container->setMinimumWidth(this->width());

    // widget
    infoContaier = new Container;
    infoContaier->setMinimumHeight(100);
    infoContaier->setMinimumWidth(this->width());
    infoContaier->setStyleSheet("border-bottom: 1px solid #CCCCCC;");

    v_box = new QVBoxLayout(infoContaier);

    h_box_child = new QHBoxLayout();
    v_box_child = new QVBoxLayout();

    v_box_1 = new QVBoxLayout();
    v_box_1->setContentsMargins(15, 0, 15, 15);
    v_box_1->addWidget(&infoNameDesktopApp);
    v_box_1->addWidget(&infoVerionApp);

    infoLabelFont = this->font();
    infoLabelFont.setWeight(QFont::Weight::Normal);

    infoMessageAboutPc.setText("Техническая информация");
    infoMessageAboutPc.setStyleSheet("border: none;"
                                     "color: rgba(0, 150, 237, 255); "
                                     "font-size: 14px;");

    infoNameDesktopApp.setText("HelperDesk Desktop");
    infoNameDesktopApp.setStyleSheet("color: #989898;");

    infoVerionApp.setText("Версия 1.0.0 x64");
    infoVerionApp.setStyleSheet("color: #A1A1A1;");
    infoVerionApp.setContentsMargins(0,3,0,0);
    infoVerionApp.setFont(infoLabelFont);

    infoAboutIpPc.setWordWrap(true);
    infoAboutIpPc.setText("Имя компьютера: " + this->pcInfo->localHostName());
    infoAboutIpPc.setFont(infoLabelFont);
    infoAboutIpPc.setStyleSheet("border: none; color: #303030;");

    infoAboutDomainName.setWordWrap(true);
    infoAboutDomainName.setText("IPv4: " + this->pcInfo->localIpAddressPc());
    infoAboutDomainName.setFont(infoLabelFont);
    infoAboutDomainName.setStyleSheet("border: none; color: #303030;");

    infoAboutPrinter.setWordWrap(true);
    infoAboutPrinter.setText("Модель принтера: " + this->pcInfo->localPrinterName());
    infoAboutPrinter.setFont(infoLabelFont);
    infoAboutPrinter.setStyleSheet("border: none; color: #303030;");


    h_box_child->addWidget(&infoMessageAboutPc, 0, Qt::AlignTop | Qt::AlignHCenter);
    v_box->addLayout(h_box_child);

    v_box_child->setContentsMargins(15, 5, 15, 0);
    v_box_child->addWidget(&infoAboutDomainName);
    v_box_child->addWidget(&infoAboutIpPc);
    v_box_child->addWidget(&infoAboutPrinter);
    v_box->addLayout(v_box_child);

    QVBoxLayout *contentLayout = new QVBoxLayout(container);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);


    link = new LinkButton("link");
    link_1 = new LinkButton("link_1");
    link_2 = new LinkButton("link_2");


    contentLayout->addWidget(link);
    contentLayout->addWidget(link_1);
    contentLayout->addWidget(link_2);
    contentLayout->addStretch();
    contentLayout->addLayout(v_box_1);


    // ***
    container->setLayout(contentLayout);

    scrollbar = new scrollArea;
    scrollbar->setAlwaysShowWhenNeeded(true);
    scrollbar->setGeometry(0,0,width(), height());
    scrollbar->setUseSmoothScroll(true);
    // ***
    scrollbar->setWidget(container);


    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->setContentsMargins(0,0,0,0);

    // ***
    mainlayout->addWidget(infoContaier);
    mainlayout->addWidget(scrollbar);

    this->setLayout(mainlayout);

    anim = new pa::PropertyAnimation(this, "pos");
}


void sidebar::toggle()
{
    this->raise();

    bool curState = _sidebar->visibleState(); // default state = false;

    if (!curState) {
        // Показываем Боковую панель
        _sidebar->anim->setStartAnimation(_sidebar->pos(), QPoint(0,0));
        _overlay->show();
    } else {
        // // скрываем Боковую панель
        _sidebar->anim->setEndAnimation(_sidebar->pos(), QPoint(-270, 0));
        _overlay->hide();
    }

    _sidebar->anim->start();
    _sidebar->setVisibleState(!curState);

}



void sidebar::setVisibleState(bool stateVisible) {
    this->isVisible = stateVisible;
}

bool sidebar::visibleState(){
    return this->isVisible;
}

void sidebar::updateState() {

    if (_sidebar->visibleState()) {
        _sidebar->toggle();
    } else {
        _sidebar->toggle();

    }
}



QSize sidebar::sizeHint() const {
  // .....
}


QSize sidebar::minimumSizeHint() const {
    return sizeHint();
}


overlay::overlay(QWidget *parent)
    : ui::uiWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint); // удаляет стандартную рамку и заголовок окна приложения
    setAttribute(Qt::WA_TranslucentBackground); // делает окно возможным полупрозрачным
    this->setStyleSheet("background-color: rgba(0, 0, 0, 40%);"); // 40% прозрачность окна
}


//
void overlay::mousePressEvent(QMouseEvent *event) {

    _sidebar->updateState();

}

