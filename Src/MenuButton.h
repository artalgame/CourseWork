#pragma once
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>
#include "DrawObject.h"
using namespace DGLE2;
using namespace std;



class MenuButton:public DrawObject
{
protected:
	ITexture *_image;
	IMusic *_isClickSound;
	IMusic *_isCursorOnSound;
	bool _playClickSound;
	bool _playCursorOnSound;
	char* _caption;//alternative text which displaied when UNDERCURSOR _buttonState
	State _state1;
public:
	MenuButton(void);
	MenuButton(Position pos, Size size,ITexture* image, IMusic* isClick, IMusic* isCursorOn, State state,char* caption);
	ITexture* GetTexture();
	void SetTexture(ITexture *image);
    State GetState();
	void SetState(State state);
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	void Draw();//draw button
	~MenuButton(void);
};

