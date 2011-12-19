#include "MenuClass.h"

MenuClass::MenuClass()
{
	_countOfObject = NULL;
	_fonImage = NULL;
	_fonMusic = NULL;
}
MenuClass::MenuClass(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state)
	:DrawObject(pos, size, state)
{
	_fonImage = fonImage;
	_fonMusic = fonMusic;
}

void MenuClass::Draw()
{
	if(_state != DEACTIVE)
	{
		if(_fonImage != NULL)
			_fonImage->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());
		if(!(_objectList.empty()))
		{
			for(int i=0; i<_objectList.size(); i++)
			{
				_objectList[i]->Draw();
			}
		}
	}
}

void MenuClass::PlayMusic(bool isLoop)
{
	_fonMusic->Play(isLoop);
}
void MenuClass::PauseMusic()
{
	_fonMusic->Pause(true);
}
void MenuClass::StopMusic()
{
	_fonMusic->Stop();
}
void MenuClass::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if((mousePos.GetX()>=_position.GetX())
		&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth())
		&&(mousePos.GetY()>=_position.GetY())
		&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight())
		&&(_state != DEACTIVE))
	{
		if(isClicked)
		{
			_state = UNDERCURSOR;
		}
		else
			if (isPressed)
			{
				_state = PRESSED;
			}
			else
			{
				_state = UNDERCURSOR;
			}

			for(int i = 0; i<_objectList.size(); i++)
			{
				_objectList[i]->Process(mousePos, isClicked, isPressed);
				if((_objectList[i]->GetState()!=DEACTIVE)&&(_objectList[i]->GetState() != NORMALSTATE))
				{
					_state = _objectList[i]->GetState();
					return;
				}
			}
	}
	else
		_state = NORMALSTATE;
}

void MenuClass::AddElement(DrawObject* newObject)
{
	newObject->SetPosition(Position(this->GetPosition().GetX()+newObject->GetPosition().GetX(),
		this->GetPosition().GetY()+newObject->GetPosition().GetY(),0));
	_objectList.push_back(newObject);
}

DrawObject* MenuClass::GetElement(int index)
{
	if((index >= 0)&&(index < _objectList.size()))
	{
		return _objectList[index];
	}
}

State MenuClass::GetState()
{
	return _state;
}
void MenuClass::SetState(State state)
{
	_state = state;
}

MenuClass::~MenuClass(void)
{
}
