#pragma once 
#include "DGLE2.h"
#include "DGLE2_EXT.h"
#include "DrawObject.h"
using namespace DGLE2;

class Cell: public DrawObject
{
private:
	ITexture* _textureSea;
	ITexture* _textureSelection;
public:
	//Constructors
	Cell(void);
	Cell(ITexture* textureSea, ITexture* textureSelection);

	//Overrided method 
	void Process(Position mousePos,bool isClicked,bool isPressed);
	void Draw();

	ITexture* Get_TextureSea(void);
	ITexture* Get_TextureSelection(void);
	State GetState();

	void Set_TextureSea(ITexture* textureSea);
	void Set_TextureSelection(ITexture* textureSelection);
	void SetState(State state);

	~Cell();
};