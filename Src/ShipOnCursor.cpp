#include "PlacementMatrix.h"
#include "ShipOnCursor.h"


ShipOnCursor::ShipOnCursor(void)
{
}

ShipOnCursor::ShipOnCursor(PlacementMatrix* ownerMatrix,
	Position pos,Size size, State state,ITexture* textureExplo,ITexture* shipTex,int countOfPalubs,bool isHorizontal , bool isDied )
	:Ship(shipTex,textureExplo,countOfPalubs,pos,size,state,isHorizontal,isDied)
{
	_ownerMatrix = ownerMatrix;
}

void ShipOnCursor::Process(Position mousePos,bool isLeftClicked,bool isLeftPressed,bool isRightClicked,bool isRightPressed)
{
	if(_state != DEACTIVE)
	{
		if(_ownerMatrix->GetState() == NORMALSTATE)
		{
			edgeHor = 0;
			edgeVert = 0;
			mousePos.SetAngle(_position.GetAngle());
			SetPosition(mousePos);
			Ship::Process(mousePos,isLeftClicked,isLeftPressed);
			if(isRightClicked)
			{
				SetIsHorizontal(GetIsHorizontal()^true);
					if(!GetIsHorizontal())
					_position.SetAngle(90);
				else
					_position.SetAngle(0);
			}
			if(isLeftClicked)
			{
				_state = DEACTIVE;
				_ownerMatrix->Process(mousePos,isLeftClicked,isLeftPressed);
			}
		}
		else
		{
			Cell* cell = _ownerMatrix->_cellUnderCursorOrPressed;
			edgeHor = _ownerMatrix->edgeHor;
			edgeVert = _ownerMatrix->edgeVert;
			SetPosition(Position(cell->GetPosition().GetX(),cell->GetPosition().GetY(),_position.GetAngle()));
			Ship::Process(mousePos,isLeftClicked,isLeftPressed);

			if(isRightClicked)
			{
				SetIsHorizontal(GetIsHorizontal()^true);
				if(!GetIsHorizontal())
					_position.SetAngle(90);
				else
					_position.SetAngle(0);
			}
			else
				if(isLeftClicked)
				{
					SetPosition(Position(_ownerMatrix->_cellPosition.GetX(),_ownerMatrix->_cellPosition.GetY(),_position.GetAngle()));
					if(_ownerMatrix->AddShip(this))
					{
						switch (_countOfPalubs)
						{
						case 1:
							_ownerMatrix->_countOf1PSh--;
							break;
						case 2:
							_ownerMatrix->_countOf2PSh--;
							break;
						case 3:
							_ownerMatrix->_countOf3PSh--;
							break;
						case 4:
							_ownerMatrix->_countOf4PSh--;
							break;
						}
						_state = DEACTIVE;
					}
				}

		}	
	}

}

/*void ShipOnCursor::Draw()
{
Ship::Draw();
}*/

ShipOnCursor::~ShipOnCursor(void)
{
}
