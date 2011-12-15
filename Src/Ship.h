
#pragma once
#include "drawobject.h"
#include <vector>
#include "ShipCell.h"
#include "DGLE2.h"
#include"DGLE2_EXT.h"
using namespace DGLE2;
using namespace std;

class Ship :
	public DrawObject
{
protected:
	bool _isHorizontal;
	ShipCell** _shipCells;
	bool _isDied;
	ITexture* _shipTex;
	ITexture* _textureExplo;
	int _countOfPalubs;
public:
	int edgeHor ;
	int edgeVert;

	Ship(void);//in position save coordinates in matrix
	Ship(ITexture* shipTex,ITexture* textureExplo,int countOfPalubs,Position pos,Size size, State state,bool isHorizontal = true, bool isDied = false);
//overrided method
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char = NULL);
	void Draw();
	State GetState();
	void SetState(State state);
//own methods
	bool GetIsDied();
	int GetCountOfPalubs();
	void SetCountOfPalubs(int count);
	void SetIsDied(bool isDied);
    bool GetIsHorizontal();
	void SetIsHorizontal(bool isHorizontal);
	ShipCell* GetCell(int index);
	~Ship(void);
};

