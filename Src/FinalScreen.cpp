#include "MainClass.h"
#include "FinalScreen.h"


FinalScreen::FinalScreen(void)
{
}

FinalScreen::FinalScreen(MainClass* ownerMainClass,	ITexture* fonTexture,char* winOrLoseCaption,IBitmapFont* font,MenuButton* goToMainMenu)
{
	_ownerMainClass = ownerMainClass;
	_fonTexture = fonTexture;
	_winOrLoseCaption = winOrLoseCaption;
	_font = font;
	_font->SetScale(2.1);
	_goToMainMenu = goToMainMenu;
}
void FinalScreen::Draw()
{
	_fonTexture->Draw2D(0,0,800,600);
	_font->Draw2D(300,200,_winOrLoseCaption,TColor4(12,278,34,255));
	_goToMainMenu->Draw();
}

char* FinalScreen::GetCaption()
{
	return _winOrLoseCaption;
}
void FinalScreen::SetCaption(char* caption)
{
	if(caption!=NULL)
	{
		_winOrLoseCaption = caption;
	}
}
void FinalScreen::Process(Position mouseState,bool isClicked,bool isPressed,char* ch)
{
	_goToMainMenu->Process(mouseState,isClicked,isPressed);
	if(_goToMainMenu->GetState() == PRESSED)
	{
		_ownerMainClass->_gameState = MAIN_MENU;
	}
}
State FinalScreen::GetState()
{
	return _state;
}
void FinalScreen::SetState(State state)
{
	_state = state;
}
FinalScreen::~FinalScreen(void)
{
}
