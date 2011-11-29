//This class describe behavior of Main menu and may be used for create own menu
// Position and Size variables will make 
#pragma once
#include "MenuButton.h"
#include <vector>
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>
#include "DrawObject.h"
using namespace DGLE2;
using namespace std;

class MenuClass :public DrawObject
{
protected:
	vector<DrawObject*> _objectList;
	int _countOfObject;
	
	IMusic* _fonMusic;
public:
	ITexture* _fonImage;
	MenuClass(void);
	MenuClass(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state);

	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	void AddElement(DrawObject* newObject);
	DrawObject* GetElement(int index);
	void PlayMusic(bool isLoop);
	void PauseMusic();
	void StopMusic();
	void Draw();
	void SetState(State state);
	State GetState();
	~MenuClass(void);
};

