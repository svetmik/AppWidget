#include "sidebar_panel.h"

Sidebar_panel::Sidebar_panel(QWidget *parent)
    : ui::uiWidget{parent}
{

    infoLabelFont = this->font();
    infoLabelFont.setWeight(QFont::Weight::Normal);

    _scrollArea = new ScrollArea(this);
    _scrollArea->setAlwaysShowWhenNeeded(true);
    _scrollArea->setUseSmoothScroll(true);

    _container = new Container(_scrollArea);
    _container->setContentsMargins(0,0,0,0);
    _container->setMinimumHeight(200);

    _layout_container = new QVBoxLayout(_container);
    _layout_container->setContentsMargins(0, 0, 0, 0);
    _layout_container->setSpacing(0);


    v_box_1 = new QVBoxLayout();
    v_box_1->setContentsMargins(15, 0, 15, 15);
    v_box_1->addWidget(&infoNameDesktopApp);
    v_box_1->addWidget(&infoVerionApp);

    infoNameDesktopApp.setText("HelperDesk Desktop");
    infoNameDesktopApp.setStyleSheet("color: #989898;");

    infoVerionApp.setText("Версия 1.0.0 x64");
    infoVerionApp.setStyleSheet("color: #A1A1A1;");
    infoVerionApp.setContentsMargins(0,3,0,0);
    infoVerionApp.setFont(infoLabelFont);

    _scrollArea->setWidget(_container);

    _link_btn = new LinkButton("btn");
    _layout_container->addWidget(_link_btn);
    _layout_container->addStretch();
    _layout_container->addLayout(v_box_1);

    // Главный лейаут самого виджета только для того, чтобы растянуть ScrollArea
    _layout_main = new QVBoxLayout(this);
    _layout_main->setContentsMargins(0, 0, 0, 0);

    this->setupHeader(_layout_main);

    _layout_main->addWidget(_scrollArea);

    this->setLayout(_layout_main);
}

void Sidebar_panel::setStyle(QWidget *widget){


    qss.setOpenStyleQss(":/UI/style.qss");

    qss.readAll();

    widget->setStyleSheet(qss.getStyle());

}

void Sidebar_panel::setupHeader(QLayout *parentLayout) {

    const auto main_header_layout = vLayout();
    const auto info_layout = hLayout();
    const auto info_text = vLayout();
    const auto header_box = createHeader();

    setStyle(this);

    if(header_box) {

        header_box->setMinimumHeight(Ui::headerHeight);
        header_box->setLayout(main_header_layout);

        if(info_layout) {

            auto row_title = infoRowTitle("Техническая информация", false);

            info_layout->addWidget(row_title, 0, Qt::AlignTop | Qt::AlignHCenter);

        }

        if(info_text) {

            info_text->setContentsMargins(Ui::margin, Ui::margin_5, Ui::margin, 0);

            info_text->addWidget(infoRowText("Имя компьютера: ", pcInfo->localHostName()));
            info_text->addWidget(infoRowText("IP-адрес (IPv4): ",  pcInfo->localIpAddressPc()));
            info_text->addWidget(infoRowText("Принтер по умолчанию: ", pcInfo->localPrinterName()));
        }
        if(main_header_layout) {

            main_header_layout->addLayout(info_layout);
            main_header_layout->addLayout(info_text);
        }
    }

    parentLayout->addWidget(header_box);
}

// qss example #header_panel
ui::uiWidget *Sidebar_panel::createHeader() {

    auto header = new Container();

    header->setObjectName("widget_container");

    return header;
}

QVBoxLayout *Sidebar_panel::vLayout() {

    auto layout = new QVBoxLayout();

    return layout;
}

QHBoxLayout *Sidebar_panel::hLayout() {

    auto layout = new QHBoxLayout();

    return layout;
}


QLabel *Sidebar_panel::infoRowTitle(const QString &text, bool wrap)
{
    auto *label = new QLabel(this);

    label->setText(text);

    label->setObjectName("widget_label_title");

    label->setWordWrap(wrap);

    return label;
}

QLabel *Sidebar_panel::infoRowText(const QString &text, bool wrap)
{
    auto *label = new QLabel(this);

    label->setText(text);

    label->setObjectName("widget_label_row");

    label->setWordWrap(wrap);

    return label;
}


QLabel *Sidebar_panel::infoRowText(const QString &text, const QString &value, bool wrap)
{
    auto *label = new QLabel(this);

    label->setText(text + " " + value);

    label->setObjectName("widget_label_row");

    label->setWordWrap(wrap);

    return label;
}

















