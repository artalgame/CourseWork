#include "MenuDropList.h"


MenuDropList::MenuDropList(Position pos, Size size,State state,int labelWidth,
	int labelHeight,TColor4 colorOfText,MenuButton* button,int countOfElement,IBitmapFont* font,ITexture* image):
DrawObject(pos, size,state)
{
	_colorOfText = colorOfText;
	_image = image;
	_button = button;
	_countOfElement = countOfElement;
	_indexOfChLabel = -1;
	_font = font;
	_button->SetPosition(Position(_position.GetX()+_size.GetWidth(),_position.GetY(),0));
	_button->SetSize(Size(_size.GetHeight(),_size.GetHeight()));
	_labelWidth = labelWidth;
	_labelHeight = labelHeight;
}

void MenuDropList::AddNewElement(MenuLabel* newElement)
{
	_labelList.push_back(newElement);
	_countOfElement++;
	_labelList[	_countOfElement-1]->SetSize(Size(_labelWidth,_labelHeight));
	_labelList[	_countOfElement-1]->SetPosition(Position(_position.GetX(),_position.GetY()+_size.GetHeight()+(_countOfElement-1)*_labelHeight,0));
	if(_indexOfChLabel < 0 )
	{
		_indexOfChLabel = 0;
		_caption = _labelList[_indexOfChLabel]->GetCaption();
	}
}

void MenuDropList::Draw()
{
	if(_state != DEACTIVE)
	{
		if(_image != NULL)
			_image->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());

		if(_button != NULL)	_button->Draw();

		if((_font != NULL)&&(_indexOfChLabel != -1))
		{
			uint x, y;
			_caption = _labelList[_indexOfChLabel]->GetCaption();
			_font->GetTextDimensions(_caption,x,y);
			x = _position.GetX()+(_size.GetWidth()-x)/2;
			y = _position.GetY()+(_size.GetHeight()-y)/2;
			_font->Draw2D(x,y,_caption,_colorOfText,_position.GetAngle());

			if(_state == UNDERCURSOR)
			{
				for(int i=0;i<_countOfElement;i++)
					_labelList[i]->Draw();
			}
		}
	}
}

void MenuDropList::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if(_state != DEACTIVE)
	{
		if(_state == NORMALSTATE)
		{
			/*if((mousePos.GetX()>=_position.GetX())
				&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth())
				&&(mousePos.GetY()>=_position.GetY())
				&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
			{
				_state = UNDERCURSOR;
			}	
			else*/
			{
				_button->Process(mousePos,isClicked,isPressed);
				if (_button->GetState() == PRESSED)
					_state = UNDERCURSOR;
			}
		}
		else
			if(_state == UNDERCURSOR)
			{
				if((mousePos.GetX()>=_position.GetX())
					&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth())
					&&(mousePos.GetY()>=_position.GetY())
					&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight()+_countOfElement*_labelHeight))
				{
					for(int i =0;i<_countOfElement;i++)
					{
						_labelList[i]->Process(mousePos,isClicked,isPressed);
						if(_labelList[i]->GetState() == PRESSED)
						{
							if(i != _indexOfChLabel)
							{
								_labelList[_indexOfChLabel]->SetState(NORMALSTATE);
								_indexOfChLabel = i;
								break;
							}
						}
					}
				}
				else
				{
					_button->Process(mousePos,isClicked,isPressed);
					if (_button->GetState() == PRESSED)
						_state = NORMALSTATE;
					if(isClicked)
				_state = NORMALSTATE;
				}
			}
			
	}
}

State MenuDropList::GetState()
{
	return _state;
}

void MenuDropList::SetState(State state)
{
	_state = state;
}

MenuLabel* MenuDropList::GetChoisedElement()
{
	return _labelList[_indexOfChLabel];
}

void MenuDropList::SetChoisedElement(int index)
{
	_indexOfChLabel = index;
	_labelList[index]->SetState(PRESSED);
}

MenuLabel* MenuDropList::GetElement(int index)
{
	return _labelList[index];
}


MenuDropList::~MenuDropList(void)
{
}
