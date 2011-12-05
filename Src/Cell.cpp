#include "Cell.h"

//Constructor
Cell::Cell(void)
{
	_textureSea = NULL;
	_textureSelection = NULL;
}

Cell::Cell(ITexture* textureSea, ITexture* textureSelection)
{
	_textureSea = textureSea;
	_textureSelection = textureSelection;
}

//Overrided method 
void Cell::Process(Position mousePos,bool isClicked,bool isPressed)
{
}

void Cell::Draw()
{
	if (_state != DEACTIVE)
	{
		if (_state != ACTIVE)
		{
			if (_state == PRESSED)
			{
				if (!_textureSea)
					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());

				if (!_textureSelection)
					_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());
			}
			else
			{
				if (!_textureSea)
					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());

				if (_state == UNDERCURSOR)
				{
					if (!_textureSelection)
						_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());
				}	
			}
		}
		else
		{
			if (!_textureSea)
				_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());
		}
	}
}

//Methods for a encapsulation
ITexture* Cell::Get_TextureSea(void)
{
	return _textureSea;
}

ITexture* Cell::Get_TextureSelection(void)
{
	return _textureSelection;
}

State Cell::GetState(void)
{
	return _state;
}

void Cell::Set_TextureSea(ITexture* textureSea)
{
	_textureSea = textureSea;
}

void Cell::Set_TextureSelection(ITexture* textureSelection)
{
	_textureSelection = textureSelection;
}

void Cell::SetState(State state)
{
	_state = state;
}

//Destructor
Cell::~Cell()
{
}