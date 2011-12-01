//this class realise behavior of button
#include "MenuButton.h"

MenuButton::MenuButton(void):DrawObject()
{
	_image = NULL;//Image that include 4 pictures for 4 State 
	_isClickSound = NULL;// Sound is played when Button is clicked
	_isCursorOnSound = NULL;//Sound is played when Button is stated under cursor
	_state = NORMALSTATE;//current state of button
	_caption = NULL;//text which will characterise our button
	_playClickSound = false;//If Click sound played yet
	_playCursorOnSound = false;//If Cursorsound played yet
	_state1 = _state;
}

MenuButton::MenuButton(Position pos, Size size,ITexture* image, IMusic* isClick, IMusic* isCursorOn,
	                   State state,char* caption):DrawObject(pos, size,state)
{
	_image = image;
	_isClickSound = isClick;
	_isCursorOnSound = isCursorOn;
	_state = state;
	_caption = caption;

     uint width, height;
	_playClickSound = false;
	_playCursorOnSound = false;
	_image->GetDimensions(width, height);
	_image->SetFrameSize(width/4, height);
}

void MenuButton::Draw()
{
	if(_image != NULL)
	_image->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle(),_state1);
}
State MenuButton::GetState()
{
	return _state;
}

ITexture* MenuButton::GetTexture()
{
	return _image;
}

void MenuButton::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)//in code which will use this method must be realize verification of click
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
				_state = PRESSED;
				if(!(_playClickSound)&&(_isClickSound != NULL))
				{
					 _playClickSound = true;
					_isClickSound->Play(false);
				}
				_state1 = UNDERCURSOR;
			}
			else
			if (isPressed)
			{
				_state = UNDERCURSOR;
				_state1 = PRESSED;
			}
			else
			{
				_state = UNDERCURSOR;
				_state1 = UNDERCURSOR;
				if(!(_playCursorOnSound)&&(_isCursorOnSound != NULL))
				{
					_playCursorOnSound = true;
					_isCursorOnSound->Play(false);
				}
				_playClickSound = false;
			}
		}
	else
	{
		_state = NORMALSTATE;
		_state1 = NORMALSTATE;
		_playClickSound = false;
		_playCursorOnSound = false;
	}
		
	}
}

void MenuButton::SetState(State state)
{
	_state = state;
}

void MenuButton::SetTexture(ITexture* image)
{
	_image = image;
}

MenuButton::~MenuButton(void)
{
//	delete(_caption);//check mistake
}
