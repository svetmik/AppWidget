#ifndef FONT_H
#define FONT_H



#include "font_styles.h"
#include "UI/widgets/basewidget.h"

class Font : public ui::uiWidget
{
    Q_OBJECT
public:
    explicit Font(QWidget *parent = nullptr);

    void loadFontForWidget(const QString &filename);

    QString fontFamily() const;

protected:
    QFontDatabase _base;

private:

    void applicationFontFamilies(const int& id_font);
    QString _data;

    int _idFont;
signals:
};

#endif // FONT_H
