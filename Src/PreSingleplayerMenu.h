//
class MainClass;
#pragma once
#include "menuclass.h"
#include "Player.h"
class PreSingleplayerMenu :
	public MenuClass
{
private:
		MainClass* _owner;
public:
	PreSingleplayerMenu(void);
	PreSingleplayerMenu(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state,MainClass* owner);
	void Draw();
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char = "");
	MainClass* GetOwner();
	~PreSingleplayerMenu(void);
};

