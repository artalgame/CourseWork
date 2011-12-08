#include "MainMenuClass.h"
#include "MainClass.h"


MainMenuClass::MainMenuClass(void):MenuClass()
{
}
MainMenuClass::MainMenuClass(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state,MainClass* owner):
MenuClass(fonImage,fonMusic,pos,size,state)
{
	_owner = owner;
}
MainClass* MainMenuClass::GetOwner()
{
	return _owner;
}
void MainMenuClass::Draw()
{
	MenuClass::Draw();
}

void MainMenuClass::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
 int bNumber = -1;

 MenuClass::Process(mousePos,isClicked,isPressed,_char);
 for(int i = 0; i<4; i++)
 {
	 State state = GetElement(i)->GetState();
	 if(state == PRESSED)
	 {
		 bNumber = i;
		 break;
	 }
 }

 switch(bNumber)
 {
 case 0:
	 _owner->_gameState = PRE_SINGLEPLAYER;
	 break;
 case 1:
	 _owner->_gameState = PRE_MULTIPLAYER;
	 break;
 case 2:
	 _owner->_gameState = SETTINGS;
	 break;
 case 3:
	 _owner ->_gameState = EXIT;
     break;
 }
	
}
State MainMenuClass::GetState()
{
	return MenuClass::GetState();
}
void MainMenuClass::SetState(State state)
{
	MenuClass::SetState(state);
}

MainMenuClass::~MainMenuClass(void)
{
}
