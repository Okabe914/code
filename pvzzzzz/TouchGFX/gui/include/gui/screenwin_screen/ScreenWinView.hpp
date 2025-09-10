#ifndef SCREENWINVIEW_HPP
#define SCREENWINVIEW_HPP

#include <gui_generated/screenwin_screen/ScreenWinViewBase.hpp>
#include <gui/screenwin_screen/ScreenWinPresenter.hpp>

class ScreenWinView : public ScreenWinViewBase
{
public:
    ScreenWinView();
    virtual ~ScreenWinView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENWINVIEW_HPP
