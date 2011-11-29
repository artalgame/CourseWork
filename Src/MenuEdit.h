#pragma once
#include "DGLE2.h"
#include "DGLE2_EXT.h"
#include <string>
#include "DrawObject.h"
using namespace std;
using namespace DGLE2;

class MenuEdit : 
	public DrawObject
{
protected:
	ITexture* _backgroundImage;
	string* _text;
	IBitmapFont* _font;
public:
	MenuEdit(void);
	MenuEdit(ITexture* backgroundImage, string* text, IBitmapFont* font, Position pos, Size size, State state);
	
	//Draw object method
	void Draw();
	//State update method
	void Process(Position mousePos,bool isClicked,bool isPressed);

	//Methods for an encapsulation
	ITexture* Get_BackgroundImage(void);
	string* Get_Text(void);
	IBitmapFont* Get_Font(void);

	void Set_BackgroundImage(ITexture* backgroundImage);
	void Set_Text(string* text);
	void Set_Font(IBitmapFont* font);

	~MenuEdit(void);
};

