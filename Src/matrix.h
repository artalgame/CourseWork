class Player;
#pragma once
#include "drawobject.h"
#include "DGLE2.h"
#include "Ship.h"
#include "Cell.h"
#include"DGLE2_EXT.h"
using namespace DGLE2;
using namespace std;
class matrix :
	public DrawObject
{
protected:
    Cell*** _cellMatrix;
	ITexture* _textureSea;//0 - normal cell, 1 - selected cell, 2 - shoted cell
	ITexture* _textureSelection;
	Size _cellSize;
	int edgeHor ;
	int edgeVert;
public:
	Player* _ownerPlayer;
	bool _isCanShot;//used by Cell and signalized, if we can shot to this cell.Used only mouse under matrix
	bool _isFriend;
	matrix(void);
	matrix(bool isFriend,bool isCanShot,ITexture* textureSelection, ITexture* textureSea,Size cellSize,Position pos, 
		Size size, State state,Player* ownerPlayer = NULL);
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	void Draw(void);
	State GetState();
	void SetState(State state);

	void AddShip(Ship* ship);
	~matrix(void);
};

