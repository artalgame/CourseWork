class matrix;
#pragma once 
#include "DGLE2.h"
#include "DGLE2_EXT.h"
#include "DrawObject.h"
using namespace DGLE2;
using namespace std;
class Cell: public DrawObject
{
protected:
	ITexture* _textureSea;//0 - normal cell, 1 - selected cell, 2 - shoted cell
	ITexture* _textureSelection;//0 - green selection without pressed mouse,1-- green selection with pressed mouse,2-red 0,3- red 1
	matrix* _ownerMatrix;
public:
	bool _isShoted;
	//Constructors
	Cell(void);
	Cell(matrix* ownerMatrix,ITexture* textureSea, ITexture* textureSelection, Position pos, Size size, State state);

	//Overrided method 
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	void Draw();

	ITexture* Get_TextureSea(void);
	ITexture* Get_TextureSelection(void);
	State GetState();

	void Set_TextureSea(ITexture* textureSea);
	void Set_TextureSelection(ITexture* textureSelection);	
	void SetState(State state);

	~Cell();
};