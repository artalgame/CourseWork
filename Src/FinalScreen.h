#pragma once
#include "MenuClass.h"
class MainClass;
class FinalScreen:public MenuClass
{
	MainClass* _ownerMainClass;
	ITexture* _fonTexture;
	char* _winOrLoseCaption;
	IBitmapFont* _font;
	MenuButton* _goToMainMenu;
public:
	FinalScreen(MainClass* ownerMainClass,	ITexture* fonTexture,char* winOrLoseCaption,IBitmapFont* font,
		MenuButton* goToMainMenu);
	void Process(Position mousePos, bool isClicked,bool isPressed,char* = NULL);
	void Draw();
	State GetState();
	void SetCaption(char* caption);
	char* GetCaption();
	void SetState(State state);
	FinalScreen(void);
	~FinalScreen(void);
};

