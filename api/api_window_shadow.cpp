#include "api_window_shadow.h"



ApiWindowShadow::ApiWindowShadow() {


}


void ApiWindowShadow::setMargins(
    const int &cxLeftWidth,
    const int &cxRightWidth,
    const int &cyTopHeight,
    const int &cyBottomHeight )
{

    m_margin = {cxLeftWidth, cxRightWidth, cyTopHeight, cyBottomHeight};

}

MARGINS ApiWindowShadow::margins() const {

    return m_margin;

}


