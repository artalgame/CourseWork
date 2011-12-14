class PlacementMatrix;
#pragma once
#include "Ship.h"
class ShipOnCursor:public Ship 
{
protected:
	PlacementMatrix* _ownerMatrix;
	Position _cursorPos;
public:
	ShipOnCursor(void);
	ShipOnCursor(PlacementMatrix* ownerMatrix,
	Position pos,Size size, State state,ITexture* textureExplo,ITexture* shipTex,int countOfPalubs,bool isHorizontal = true, bool isDied = false);
	void Process(Position mousePos,bool isLeftClicked,bool isLeftPressed,bool isRightClicked,bool isRightPressed);
	//void Draw();
	~ShipOnCursor(void);
};

