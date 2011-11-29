#include "MenuEdit.h"


MenuEdit::MenuEdit(void):DrawObject()
{
	_backgroundImage = NULL;
	_text = NULL;
	_font = NULL;
}

MenuEdit::MenuEdit(ITexture* backgroundImage, string* text, IBitmapFont* font, Position pos, Size size, State state):DrawObject(pos, size, state)
{
	_backgroundImage = backgroundImage;
	_text = text;
	_font = font;
}

void MenuEdit::Draw(void)
{
	if(_backgroundImage != NULL)
		_backgroundImage->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());

	if(_font != NULL)
	{
		TColor4 color = TColor4(0,0,0,255);
		uint x, y;
		_font->GetTextDimensions(_text->c_str() ,x,y);
		x = _position.GetX()+(_size.GetWidth()-x)/2;
		y = _position.GetY()+(_size.GetHeight()-y)/2;
		_font->Draw2D(x,y,_text->c_str(),color,_position.GetAngle());
	}
}

void MenuEdit::Process(Position mousePos,bool isClicked,bool isPressed)
{
	if(_state != DEACTIVE)
	{
		if((mousePos.GetX()>=_position.GetX())
			&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth())
			&&(mousePos.GetY()>=_position.GetY())
			&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
		{
			if(isClicked)
			{
				if(_state != PRESSED)
					_state = PRESSED;
				else
					_state = UNDERCURSOR;
			}
			else
			if(_state != PRESSED)
				{
					_state = UNDERCURSOR;
				}
		}
		else
		if(_state != PRESSED)
		{
			_state = NORMALSTATE;
		}
	}
}

//Methods for an encapsulation
ITexture* MenuEdit::Get_BackgroundImage(void)
{
	return _backgroundImage;
}

string* MenuEdit::Get_Text(void)
{
	return _text;
}

IBitmapFont* MenuEdit::Get_Font(void)
{
	return _font;
}

void MenuEdit::Set_BackgroundImage(ITexture* backgroundImage)
{
	_backgroundImage = backgroundImage;
}

void MenuEdit::Set_Text(string* text)
{
	_text = text;
}

void MenuEdit::Set_Font(IBitmapFont* font)
{
	_font = font;
}

MenuEdit::~MenuEdit(void)
{
}
