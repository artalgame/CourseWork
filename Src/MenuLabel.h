#pragma once
#include <vector>
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>
#include "DrawObject.h"
using namespace DGLE2;
using namespace std;

//it's class copy behavior of simple label
class MenuLabel :
	public DrawObject
{
protected:
	IBitmapFont* _font;//font for caption displaying
	char* _caption;
	ITexture* _fonImage;
public:	
	//color for each label state
	//they are maden special like PUBLIC because We don't see sence to make methods GET and SET for one string of code 
	TColor4 _normalColor;
	TColor4 _underCursorColor;
	TColor4 _selectColor;
	TColor4 _deactiveColor;

	MenuLabel(void);
	MenuLabel(char* caption, IBitmapFont* font, TColor4 normalColor, TColor4 underCursorColor,TColor4 selectColor,
		TColor4 deactiveColor,ITexture* fonImage,Position pos, Size size, State state);

	void Process(Position mousePos,bool isClicked,bool isPressed);
	void Draw();
  
	IBitmapFont* GetFont();
	void SetFont(IBitmapFont* newFont);

	char* GetCaption();
	void SetCaption(char* newCaption);

	ITexture* GetFonImage();
	void SetFonImage(ITexture* newFonImage);

	State GetState();
	void SetState(State state);

	~MenuLabel(void);
};

