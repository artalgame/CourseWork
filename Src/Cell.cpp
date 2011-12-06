#include "Cell.h"

//Constructor
Cell::Cell(void)
{
	_textureSea = NULL;
	_textureSelection = NULL;
}

Cell::Cell(ITexture* textureSea, ITexture* textureSelection, Position pos, Size size, State state):DrawObject(pos, size, state)
{
	_textureSea = textureSea;
	_textureSelection = textureSelection;

	uint width, height;
	_textureSea->GetDimensions(width, height);
	_textureSea->SetFrameSize(width, height/3);
}

//Overrided method 
void Cell::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if((mousePos.GetX()>=_position.GetX())
			&& (mousePos.GetX()<=_position.GetX()+_size.GetWidth())
			&& (mousePos.GetY()>=_position.GetY())
			&& (mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
		{
			if  (!((_state == NORMALSTATE) && (isPressed || isClicked)))
			{
			if((isClicked || isPressed))
				_state = PRESSED;
			else 
				_state = UNDERCURSOR;
			}
		}
		else
		{
			if(!(isClicked || isPressed))
			{
				_state = NORMALSTATE;
			}
		}
}

void Cell::Draw()
{
	if (_state != DEACTIVE)
	{
		if (_state != ACTIVE)
		{
			if (_state == PRESSED)
			{
				if (_textureSea != NULL)
					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 1);

				if (_textureSelection != NULL)
					_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());
			}
			else
			{
				if (_textureSea != NULL)
					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 0);

				if (_state == UNDERCURSOR)
				{
					if (_textureSelection != NULL)
						_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle());
				}	
			}
		}
		else
		{
			if (_textureSea != NULL)
				_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 2);
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