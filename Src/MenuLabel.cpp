#include "MenuLabel.h"

MenuLabel::MenuLabel()
{
	_caption = NULL;
	_font = NULL;
	_normalColor = NULL;
	_underCursorColor = NULL;
	_selectColor = NULL;
	_deactiveColor = NULL;
	_fonImage = NULL;
}
MenuLabel::MenuLabel(char* caption, IBitmapFont* font, TColor4 normalColor, TColor4 underCursorColor,TColor4 selectColor,
	TColor4 deactiveColor,ITexture* fonImage,Position pos, Size size, State state):DrawObject(pos,size,state)
{
	_caption = caption;
	_font = font;
	_normalColor = normalColor;
	_underCursorColor = underCursorColor;
	_selectColor = selectColor;
	_deactiveColor = deactiveColor;
	_fonImage = fonImage;
}

void MenuLabel::Draw()
{
	if(_fonImage != NULL)
		_fonImage->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());

	if(_font != NULL)
	{
		TColor4 color;
		switch (_state)
		{
		case NORMALSTATE:
			color = _normalColor;
			break;
		case UNDERCURSOR:
			color = _underCursorColor;
			break;
		case PRESSED:
			color = _selectColor;
			break;
		case DEACTIVE:
			color = _deactiveColor;
		}
		uint x, y;
		_font->GetTextDimensions(_caption,x,y);
		x = _position.GetX()+(_size.GetWidth()-x)/2;
		y = _position.GetY()+(_size.GetHeight()-y)/2;
		_font->Draw2D(x,y,_caption,color,_position.GetAngle());
	}
}

void MenuLabel::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
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

IBitmapFont* MenuLabel::GetFont()
{
	return _font;
}
void MenuLabel::SetFont(IBitmapFont* newFont)
{
	_font = newFont;
}

char* MenuLabel::GetCaption()
{
	return _caption;
}
void MenuLabel::SetCaption(char* newCaption)
{
	_caption = newCaption;
}

ITexture* MenuLabel::GetFonImage()
{
	return _fonImage;
}
void MenuLabel::SetFonImage(ITexture* newFonImage)
{
	_fonImage = newFonImage;
}

State MenuLabel::GetState()
{
	return _state;
}
void MenuLabel::SetState(State state)
{
	_state = state;
}
MenuLabel::~MenuLabel(void)
{
}
