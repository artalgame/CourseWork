#include "matrix.h"
#include "Cell.h"

//Constructor
Cell::Cell(void)
{
	_textureSea = NULL;
	_textureSelection = NULL;
}

Cell::Cell(matrix* ownerMatrix,ITexture* textureSea, ITexture* textureSelection,
	Position pos, Size size, State state):DrawObject(pos, size, state)
{
	_textureSea = textureSea;
	_textureSelection = textureSelection;
	if(_textureSea != NULL)
	{
		uint width, height;
		_textureSea->GetDimensions(width, height);
		_textureSea->SetFrameSize(width/3, height);
		_textureSelection->GetDimensions(width,height);
		_textureSelection->SetFrameSize(width/2, height/2);
	}
	_ownerMatrix = ownerMatrix;
	_isShoted = false;
	_isNearShip = false;
	_isShipCell = false;
}

//Overrided method 
void Cell::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if((_state != DEACTIVE)&&(_textureSea != NULL))
	{
		if((mousePos.GetX()>=_position.GetX())
			&& (mousePos.GetX()<=_position.GetX()+_size.GetWidth())
			&& (mousePos.GetY()>=_position.GetY())
			&& (mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
		{
			if((isClicked || isPressed))
			{
				_state = PRESSED;
				if(_ownerMatrix->_isCanShot)
					if(_isShoted == false)
					{
						_isShoted = true;
						_ownerMatrix->_isCanShot = false;
					}
			}
			else 
				_state = UNDERCURSOR;
		}
		else
		{			
			_state = NORMALSTATE;
		}
	}
}

void Cell::Draw()
{
	if ((_state != DEACTIVE)&&(_textureSea != NULL))
	{
		/*if (_state != ACTIVE)
		{*/
		if(!_isShoted)
		{
			if (_state == PRESSED)
			{
				if (_textureSea != NULL)

					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 1);

				if (_textureSelection != NULL)
					if((_ownerMatrix->_isCanShot))
						_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(),1);
					else
						_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(),3);
			}
			else
				if (_state == UNDERCURSOR)
				{

					if (_textureSea != NULL)
						_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 1);
					if(_textureSelection != NULL)
						if((_ownerMatrix->_isCanShot))
							_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(),0);
						else
							_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(),2);
				}
				else
					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 0);

		}
		else
		{
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

void Cell::SetOwnerMatrix(matrix* ownerMatrix)
{
	_ownerMatrix = ownerMatrix;
}

matrix* Cell::GetOwnerMatrix()
{
   return _ownerMatrix;
}

//Destructor
Cell::~Cell()
{
}