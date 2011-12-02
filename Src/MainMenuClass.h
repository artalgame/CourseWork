class MainClass;
#pragma once
#include "menuclass.h"
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>

using namespace DGLE2;
using namespace std;

class MainMenuClass:
	public MenuClass
{
private:
	MainClass* _owner;
public:
	MainMenuClass(void);
	MainMenuClass(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state,MainClass* owner);
	void Draw();
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char = "");
	void SetState(State state);
	 State GetState();
	MainClass* GetOwner();
	~MainMenuClass(void);
};

