#include <gui/menu_screen/MenuView.hpp>

extern int winNum;

MenuView::MenuView()
{

}

void MenuView::setupScreen()
{
    MenuViewBase::setupScreen();
		Unicode::snprintf(textBuffer, TEXT_SIZE, "%d", winNum);
		text.invalidate();
}

void MenuView::tearDownScreen()
{
    MenuViewBase::tearDownScreen();
}
void MenuView::funcHelp()
{
	modalWindowhelp.setVisible(true);
	modalWindowhelp.invalidate();
}
void MenuView::funcBack()
{
	modalWindowhelp.setVisible(false);
	modalWindowhelp.invalidate();
}