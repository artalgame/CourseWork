#pragma once
#include "DGLE2.h"
#include "DGLE2_EXT.h"
#include <string>
#include "DrawObject.h"
#include <conio.h>
using namespace std;
using namespace DGLE2;

class MenuEdit : 
	public DrawObject
{
protected:
	ITexture* _backgroundImage;
	string _text;
	IBitmapFont* _font;
	IInput* _input;
	TColor4* _color;
	int _inputCharCounter;
	bool _isMarkered;
	bool _isWrited;
public:
	MenuEdit(void);
	MenuEdit(ITexture* backgroundImage, string text, IBitmapFont* font, IInput* input, Position pos, Size size, State state, TColor4* color = new TColor4(0, 0, 0, 255));
	
	//Draw object method
	void Draw();
	//State update method
	void Process(Position mousePos,bool isClicked,bool isPressed);

	//Methods for an encapsulation
	ITexture* Get_BackgroundImage(void);
	string Get_Text(void);
	IBitmapFont* Get_Font(void);
	IInput* Get_Input(void);
	TColor4* Get_Color(void);
	State GetState();

	void Set_BackgroundImage(ITexture* backgroundImage);
	void Set_Text(string text);
	void Set_Font(IBitmapFont* font);
	void Set_Input(IInput* input);
	void Set_Color(TColor4* color);
	void SetState(State state);

	~MenuEdit(void);
};

