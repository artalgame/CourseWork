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
	if(_ownerMatrix->GetState() != UNDERCURSOR)
	{
		SetPosition(mousePos);
		Ship::Process(mousePos,isLeftClicked,isLeftPressed);
		if(isRightClicked)
		{
			SetIsHorizontal(GetIsHorizontal()^true);
		}
		if(isLeftClicked)
		{
			_state = DEACTIVE;
			_ownerMatrix->Process(mousePos,isLeftClicked,isLeftPressed);
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
