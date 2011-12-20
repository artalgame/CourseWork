#include "Ship.h"
#include "matrix.h"
#include "ShipCell.h"


ShipCell::ShipCell(void)
{
}

ShipCell::ShipCell(int numberOfCell,matrix* ownerMatrix,Ship* ownerShip,ITexture* textureShip,ITexture* textureExplo,
	ITexture* textureSea, ITexture* textureSelection, Position pos, Size size, State state)
	:Cell(ownerMatrix,textureSea,textureSelection, pos,size,state)
{
	_numberOfCell = numberOfCell;
	_ownerShip = ownerShip;
	_textureShip = textureShip;
	_textureExplo = textureExplo;
	_isExplo = false;
	uint x,y;
	_textureShip->GetDimensions(x,y);
	_textureShip->SetFrameSize(x/_ownerShip->GetCountOfPalubs(),y/2);
	_textureExplo->GetDimensions(x,y);
	_textureExplo->SetFrameSize(x/5,y/5);
	_isShipCell = true;
	_currentFrameForExplo = 0;
}

void ShipCell::Draw()
{

	if(_state != DEACTIVE)
	{	
		Cell::Draw();
		if((_isExplo))
		{
			_textureExplo->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),0,_currentFrameForExplo);
		}
		else

			if(_textureShip != NULL)
			{
				if(_ownerShip->GetIsDied())
				{
					_textureShip->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle(),_ownerShip->GetCountOfPalubs()+_numberOfCell);
				}
				else
					if(((_ownerMatrix != NULL)&&(_ownerMatrix->_isFriend))||(_ownerMatrix == NULL))
						_textureShip->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle(),_numberOfCell);
			}

	}
}
bool ShipCell::GetShot()
{
	if((!_isExplo )&&(!_ownerShip->GetIsDied()))
	{
	_isExplo = true;
	Cell::_isShoted = false;
	_ownerShip->_isWasAttacked = true;
	return true;
	}
	else 
		return false;
}
void ShipCell::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{

	Cell::Process(mousePos,isClicked,isPressed);
	if(_ownerShip->GetIsDied())
	{
		_isExplo = false;
	}
	else
	{
		if(_state == PRESSED)
		{
			if(!(_ownerMatrix->_isFriend))
			{
				_isExplo = true;
				Cell::_isShoted = false;
				_ownerShip->_isWasAttacked = true;
			}
		}
		if(_isExplo)
		{
			_currentFrameForExplo++;
			_currentFrameForExplo%=24;
		}
	}
}
ShipCell::~ShipCell(void)
{
}
