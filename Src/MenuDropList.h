#pragma once
#include "drawobject.h"
#include "MenuButton.h"
#include "MenuLabel.h"
#include <vector>
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>
using namespace DGLE2;
using namespace std;

class MenuDropList :
	public DrawObject
{
protected:
	MenuButton* _button;
	vector<MenuLabel*> _labelList;
	char* _caption;
	int _countOfElement;
	int _indexOfChLabel;
	IBitmapFont* _font;//font of text
	ITexture* _image;
	TColor4 _colorOfText;
public:
	//constructors
	//MenuDropList(void);
	MenuDropList(Position pos, Size size,TColor4 colorOfText,MenuButton* button = NULL,int countOfElement = -1,IBitmapFont* font = NULL,ITexture* image = NULL);

	//virtual methods of DrawObject class
	void Process(Position mousePos,bool isClicked,bool isPressed);
	void Draw();
	State GetState();
	void SetState(State state);

	//own methods
	MenuLabel* GetChangedElement();
	void SetChangedElement(int index);

	MenuLabel* GetIndexElement(int index);
	void AddNewElement(MenuLabel* newElement);

	~MenuDropList(void);
};

