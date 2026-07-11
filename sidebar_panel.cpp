#include "sidebar_panel.h"

Sidebar_panel::Sidebar_panel(QWidget *parent)
    : ui::uiWidget{parent}
{
    infoLabelFont = this->font();
    infoLabelFont.setWeight(QFont::Weight::Normal);

    _scrollArea = new ScrollArea(this);
    _scrollArea->setAlwaysShowWhenNeeded(true);
    _scrollArea->setUseSmoothScroll(true);

    // Главный лейаут самого виджета только для того, чтобы растянуть ScrollArea
    _layout_main = new QVBoxLayout(this);
    _layout_main->setContentsMargins(0, 0, 0, 0);

    this->setupHeader(_layout_main);
    this->setupMain(_scrollArea);

    _layout_main->addWidget(_scrollArea);

    this->setLayout(_layout_main);
}




void Sidebar_panel::setupHeader(QLayout *parentLayout) {

    const auto header_box = createHeader();
    const auto main_header_layout = vLayout();

    const auto info_layout = hLayout();
    const auto info_text = vLayout();

    if(!header_box) return;

    header_box->setMinimumHeight(Ui::headerHeight);

    header_box->setLayout(main_header_layout);
    main_header_layout->setContentsMargins(15,5,15,0);

    info_layout->addWidget(infoRowTitle("Техническая информация", false), 0, Qt::AlignTop | Qt::AlignHCenter);

    info_text->addWidget(infoRowText("Имя компьютера", pcInfo->localHostName()));
    info_text->addWidget(infoRowText("IP-адрес (IPv4)",  pcInfo->localIpAddressPc()));
    info_text->addWidget(infoRowText("Принтер по умолчанию", pcInfo->localPrinterName()));

    info_text->setContentsMargins(QMargins(10,0,5,8));

    //row title
    main_header_layout->addLayout(info_layout);
    // rows text
    main_header_layout->addLayout(info_text);

    parentLayout->addWidget(header_box);
}

void Sidebar_panel::setupMain(ScrollArea *parent) {

    const auto main_box = createMain();
    const auto main_layout_box = vLayout();

    const auto footer_layout = vLayout();

    if(!main_box) return ;

    main_box->setMinimumHeight(Ui::kMinHeight);
    main_box->setLayout(main_layout_box);

    main_layout_box->setSpacing(0);

    footer_layout->setContentsMargins(15,0,15,15);

    const auto appName = infoRowText("HelperDesk");
    appName->setObjectName("widget_label_appName");

    const auto appVersion = infoRowText("Версия 1.0.4 x64");
    appVersion->setObjectName("widget_label_appVersion");
    appVersion->setContentsMargins(0,3,0,0);
    appVersion->setFont(infoLabelFont);

    footer_layout->addWidget(appName);
    footer_layout->addWidget(appVersion);

    main_layout_box->addStretch();
    main_layout_box->addLayout(footer_layout);


    //setStyle(this);

    parent->setWidget(main_box);

}

// qss example #header_panel
ui::uiWidget *Sidebar_panel::createHeader() {

    auto header = new Container();

    header->setObjectName("widget_container_header");

    return header;
}


ui::uiWidget *Sidebar_panel::createMain() {

    auto main = new Container();

    main->setContentsMargins(0,0,0,0);

    main->setObjectName("widget_container_main");

    return main;
}

QVBoxLayout *Sidebar_panel::vLayout(QWidget *parent) {

    auto layout = new QVBoxLayout(parent);

    layout->setContentsMargins(0,0,0,0);

    return layout;
}

QHBoxLayout *Sidebar_panel::hLayout(QWidget *parent) {

    auto layout = new QHBoxLayout(parent);

    layout->setContentsMargins(0,0,0,0);

    return layout;
}


QLabel *Sidebar_panel::infoRowTitle(const QString &text, bool wrap)
{
    auto *label = new QLabel(this);

    label->setText(QString("%1").arg(text));

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

    const auto row = QString("%1: %2")
                         .arg(text)
                         .arg(value);
    label->setText(row);
    label->setObjectName("widget_label_row");
    label->setWordWrap(wrap);

    return label;
}

















