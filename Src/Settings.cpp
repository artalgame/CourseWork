#include "MainClass.h"
#include "Settings.h"


Settings::Settings(void)
{
}
Settings::Settings(MainClass*ownerClass, ITexture* fonImage,IBitmapFont* font,IInput* input)
{
	_ownerMainClass = ownerClass;
	_fonImage = fonImage;
	_font = font;
	_input = input;
	_strings =  new vector<string*>(0);
}

void Settings::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	bool press;
	_input->GetKey(KEY_ESCAPE,press);
	if(press)
	{
		_ownerMainClass->_gameState = MAIN_MENU;
	}
}

void Settings::Draw()
{
	_fonImage->Draw2D(0,0,800,600,0);
	for(int i = 0; i<_strings->size();i++)
	{
		_font->Draw2D(280,170+i*30,(*_strings)[i]->c_str(),TColor4(0,0,0,255),0);
	}
}

void Settings::AddString(string* s)
{
	_strings->push_back(s);
}
State Settings::GetState()
{
	return _state;
}
void Settings::SetState(State state)
{
	_state = state;
}

Settings::~Settings(void)
{
}
