#include "MenuDropList.h"


MenuDropList::MenuDropList(Position pos, Size size,TColor4 colorOfText,MenuButton* button = NULL,int countOfElement = -1,IBitmapFont* font = NULL,ITexture* image):
DrawObject(pos, size)
{
	_colorOfText = colorOfText;
	_image = image;
	_button = button;
	_countOfElement = countOfElement;
	_indexOfChLabel = -1;
	_font = font;
	_button->SetPosition(pos);
}

void MenuDropList::AddNewElement(MenuLabel* newElement)
{
	_labelList.push_back(newElement);
	_countOfElement++;
}

void MenuDropList::Draw()
{
	if(_image != NULL)
		_image->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());
	if(_button != NULL)
	if(_font != NULL)
	{
		uint x, y;
		_font->GetTextDimensions(_caption,x,y);
		x = _position.GetX()+(_size.GetWidth()-x)/2;
		y = _position.GetY()+(_size.GetHeight()-y)/2;
		_font->Draw2D(x,y,_caption,_colorOfText,_position.GetAngle());
		if(_state != DEACTIVE)
		{
			for(int i=0;i<_countOfElement;i++)
				_labelList[i]->Draw();
		}
	}
}

void MenuDropList::Process(Position mousePos,bool isClicked,bool isPressed)
{
	if(_state != DEACTIVE)
	{
		if((_state = NORMALSTATE)
			&&(mousePos.GetX()>=_position.GetX())
			&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth()+_button->GetSize().GetWidth())
			&&(mousePos.GetY()>=_position.GetY())
			&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight()+_button->GetSize().SetHeight()))
		{
		}
			if(isClicked)
			{
				if(_state != PRESSED)
					_state = PRESSED;
				else
					_state = UNDERCURSOR;
			}
		/*	else
				if (isPressed)
				{
					_state = PRESSED;
				}*/
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

MenuDropList::~MenuDropList(void)
{
}
