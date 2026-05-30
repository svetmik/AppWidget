
#ifndef OVERLAYBOX
#define OVERLAYBOX

#include "../widgets/basewidget.h"
#include "box.h"

class OverlayBox : public ui::uiWidget {

    Q_OBJECT

public:

    explicit  OverlayBox(QWidget *parent = nullptr);

    void bodyText(const QString &text);

    QPointer<Box> moduleBox;
    
protected:

    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:


    void centerModuleBox();

    void init();

    void boxSize();

};


#endif // OVERPLAYBOX
