class MainClass;
#pragma once
#include "drawobject.h"
#include <vector>
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>
using namespace DGLE2;
using namespace std;
class Settings :
	public DrawObject
{
protected:
	MainClass* _ownerMainClass;
	ITexture* _fonImage;
    vector<string*>* _strings;
	IBitmapFont* _font;
	IInput* _input;
public:
	Settings(void);
	Settings(MainClass* ownerClass, ITexture* fonImage,IBitmapFont* font,IInput* input);
	void Draw();
    void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	State GetState();
	void SetState(State state);
	void AddString(string* s);
	~Settings(void);
};

