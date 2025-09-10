#ifndef SCREENWINPRESENTER_HPP
#define SCREENWINPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenWinView;

class ScreenWinPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenWinPresenter(ScreenWinView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenWinPresenter() {};

private:
    ScreenWinPresenter();

    ScreenWinView& view;
};

#endif // SCREENWINPRESENTER_HPP
