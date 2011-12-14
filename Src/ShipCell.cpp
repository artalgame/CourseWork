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
}

void ShipCell::Draw()
{
	
	if(_state != DEACTIVE)
	{	
		Cell::Draw();
			if(_isExplo)
			{
				_textureExplo->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),0,0);
			}
			else
				if(_textureShip != NULL)
				{
					if(_ownerShip->GetIsDied())
					{
						_textureShip->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle(),_ownerShip->GetCountOfPalubs()+_numberOfCell);
					}
					else
						_textureShip->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle(),_numberOfCell);
				}

	}
}
void ShipCell::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	Cell::Process(mousePos,isClicked,isPressed);
	if(_state == PRESSED)
	{
		if(!(_ownerMatrix->_isFriend))
		{
			_isExplo = true;
		}
	}
}
ShipCell::~ShipCell(void)
{
}
