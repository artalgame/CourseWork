class Ship;
#pragma once
#include "cell.h"
#include "DGLE2.h"
#include "Cell.h"
#include"DGLE2_EXT.h"
#include"SoundClass.h"
using namespace DGLE2;
using namespace std;


class ShipCell :
	public Cell
{
private:
	Ship* _ownerShip;
	ITexture* _textureShip;//This texture will save two pictures good ship and bad ship(max 8 pictures 4*2)
	ITexture* _textureExplo;//one texture of explo
public:
	int _numberOfCell;
	int _currentFrameForExplo;
	bool _isExplo;
	ShipCell(void);
	ShipCell(int nubmerOfCell,matrix* _ownerMatrix,Ship* ownerShip,ITexture* _textureShip,ITexture* _textureExplo,
		ITexture* textureSea, ITexture* textureSelection, Position pos, Size size, State state);
	void Draw();
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	bool GetShot();
	void FromString(string* s);
	string* ToString();
	~ShipCell(void);
};

