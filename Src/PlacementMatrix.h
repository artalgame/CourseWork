#pragma once
#include "drawobject.h"
#include "matrix.h"
#include "ShipOnCursor.h"
class PlacementMatrix :
	public matrix
{
	IBitmapFont* _font;
	
	
	bool isLeftMousePressed;
	bool isRightMousePressed;
	bool isLeftMouseClicked;
	bool isRightMouseClicked;
	TMouseStates mouseState;
	
	ShipOnCursor* _cursorShip;
	IInput* _input;
public:
	ITexture* _textureExplo;
	ITexture* _4PShip;
	ITexture* _3PShip;
	ITexture* _2PShip;
	ITexture* _1PShip;
	vector<Ship*>* _listOfShip;
	bool _isRightFilled;
	int _countOf4PSh;
	int _countOf3PSh;
	int _countOf2PSh;
	int _countOf1PSh;
	PlacementMatrix(void);
	PlacementMatrix(IInput* input,ITexture* textureExplo,ITexture* P4Ship,ITexture* P3Ship,ITexture* P2Ship,ITexture* P1Ship,IBitmapFont* font, 
		bool isFriend,bool isCanShot,ITexture* textureSelection, ITexture* textureSea,Size cellSize,
		Position pos,Size size, State state,Player* ownerPlayer = NULL);
	//overrided method
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);

	void Draw();

	State GetState();
	void SetState(State state);
	~PlacementMatrix(void);
};

