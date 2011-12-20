class Player;
#pragma once
#include "drawobject.h"
#include "DGLE2.h"
#include "Ship.h"
#include "Cell.h"
#include <time.h>
#include"DGLE2_EXT.h"
using namespace DGLE2;
using namespace std;
class matrix :
	public DrawObject
{
protected:
    
	
public:
	bool _isWasAttacked;
	ITexture* _textureSea;//0 - normal cell, 1 - selected cell, 2 - shoted cell
	ITexture* _textureSelection;
	Size _cellSize;
	Cell*** _cellMatrix;
	Cell* _cellUnderCursorOrPressed;
	Position _cellPosition;//position of cell where was pressed or undercursored
	int edgeHor ;
	int edgeVert;
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

	bool AddShip(Ship* ship);
	matrix* GenretateMatrix(ITexture* _4PShip,ITexture* _3PShip,ITexture* _2PShip,ITexture* _1PShip,ITexture* _textureExplo,vector<Ship*>** ships);
	void SetPosition(Position pos);
	~matrix(void);
};

