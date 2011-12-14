#include "PreSingleplayerMenu.h"
#include "MainClass.h"

PreSingleplayerMenu::PreSingleplayerMenu(void)
{
}
PreSingleplayerMenu::PreSingleplayerMenu(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state,MainClass* owner):
MenuClass(fonImage,fonMusic,pos,size,state)
{
	_owner = owner;
}

void PreSingleplayerMenu::Draw()
{
	MenuClass::Draw();
}

void PreSingleplayerMenu::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	MenuClass::Process(mousePos,isClicked,isPressed, _char);
	if(_objectList[0]->GetState() == PRESSED)
	{
		_owner->_gameState = MAIN_MENU;
	}
	if(_objectList[1]->GetState() == PRESSED)
	{
		_owner->_gameState = SINGLEPLAYER;
	}
}
PreSingleplayerMenu::~PreSingleplayerMenu(void)
{
}
