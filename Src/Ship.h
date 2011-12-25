
#pragma once
#include "drawobject.h"
#include <vector>
#include "SoundClass.h"
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
	bool _isDied;
	ITexture* _shipTex;
	ITexture* _textureExplo;
	int _countOfPalubs;
	void DrawContur();
public:
	int edgeHor ;
	int edgeVert;
	bool _isWasAttacked;
	ShipCell** _shipCells;
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
	void SetPosition(Position pos);
	string* ToString();
	void FromString(string* s);
	ShipCell* GetCell(int index);
	~Ship(void);
};

