#pragma once
#include "DrawObject.h"
#include "MenuButton.h"
#include "MenuLabel.h"
#include "MenuEdit.h"
//#include "MenuClass.h"
//#include "matrix.h"
#include "PlacementMatrix.h"
#include "PreSingleplayerMenu.h"
#include "MenuDropList.h"
#include "FinalScreen.h"
#include "size.h"
#include "SinglePlayerMenu.h"
#include "Settings.h"
#include "MainMenuClass.h"
#include "Position.h"
#include <vector>
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <string>
using namespace DGLE2;
using namespace std;
//add new element if neccesarry
enum GameState{LOAD,MAIN_MENU,SETTINGS,PRE_SINGLEPLAYER,SINGLEPLAYER,PRE_MULTIPLAYER,MULTIPLAYER,EXIT,FINAL};

class MainClass
{
private:
	//Here is all objects which used ib GAME
	
	IResourceManager *pResourceManager;
	IRender2D *pRender2D;
	IRender *pRender;
	
	
	
	IMusic* click;
	IMusic* cursorOn;
	MenuButton* button;
	MenuLabel* newLabel;
	bool isMouseClicked;
	bool isMousePressed;
	MainMenuClass* mainMenu;
	PreSingleplayerMenu* preSPMenu;
	IEngineCore *pEngineCore;
	IInput *pInput;
public:
	FinalScreen* _finalScreen;
	SinglePlayerMenu* SPMenu;
	Settings* settings;
	GameState _gameState;
	MainClass(void);
	MainClass(IEngineCore* EngineCore,IResourceManager* ResourceManager, IRender2D* Render2D, 
		IRender* Render,IInput *Input);
	void LOADER();
	void PROCESS();
	void DRAW();
	void FINALIZATOR();
	~MainClass(void);
};

