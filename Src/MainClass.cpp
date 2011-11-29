#include "MainClass.h"

MainClass::MainClass(void)
{
}
MainClass::MainClass(IEngineCore* EngineCore,IResourceManager* ResourceManager, IRender2D* Render2D, 
	IRender* Render,IInput *Input)
{
	pEngineCore = EngineCore;
	pResourceManager = ResourceManager;
	pRender2D = Render2D;
	pRender = Render;
	pInput = Input;
	_gameState = MAIN_MENU;
}

void MainClass::LOADER()
{
	IBitmapFont* font;


	pResourceManager->Load("..\\Data\\music\\FonMusic1.mp3",(IEngBaseObj*&)pFonMusic);
	pResourceManager->Load("..\\Data\\sounds\\buttons\\click.mp3",(IEngBaseObj*&)click);
	pResourceManager->Load("..\\Data\\sounds\\buttons\\CursorOn.mp3",(IEngBaseObj*&)cursorOn);
	pResourceManager->Load("..\\Data\\textures\\fon1.jpg",(IEngBaseObj*&)pExitButton);

	mainMenu = new MenuClass(pExitButton,pFonMusic,Position(0,0,0),Size(800,600),NORMALSTATE);
	pResourceManager->Load("..\\Data\\textures\\buttons\\singlePlayerBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu->AddElement(new MenuButton(Position(50,50,0),Size(64,64),pExitButton,click,cursorOn,NORMALSTATE,"single player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\singlePlayerBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu->AddElement(new MenuButton(Position(150,150,0),Size(64,64),pExitButton,click,cursorOn,NORMALSTATE,"Great button"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\multiPlayerBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu->AddElement(new MenuButton(Position(150,50,0),Size(64,64),pExitButton,click,cursorOn,DEACTIVE,"multi player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\settingBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu->AddElement(new MenuButton(Position(250,50,0),Size(64,64),pExitButton,click,cursorOn,DEACTIVE,"settings"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\exitBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu->AddElement(new MenuButton(Position(350,50,0),Size(64,64),pExitButton,click,cursorOn,NORMALSTATE,"exit"));

	pResourceManager->Load("..\\Data\\fonts\\font1.dft",(IEngBaseObj*&)font);
	newLabel =new  MenuLabel("Label",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),TColor4(48,100),pExitButton,Position(300,300,0),Size(300,100),NORMALSTATE);
	mainMenu->AddElement(newLabel);
	
	mainMenu->_fonImage->Draw2DSimple(0,0);
	mainMenu->PlayMusic(true);
	
}

void MainClass::PROCESS()
{
	TMouseStates mouseState;
	bool isMouseClicked=false;
	bool isMousePressed=false;

	pInput->GetMouseStates(mouseState);
	if(mouseState.bLeftButton)
	{
		isMousePressed = true;

	}
	else
		if (isMousePressed)
		{
			isMouseClicked = true;
			isMousePressed = false;
		}
		else
		{
			isMouseClicked = false;
			isMousePressed = false;
		}

		Position mousePos(mouseState.iX,mouseState.iY,0);
		mainMenu->Process(mousePos,isMouseClicked,isMousePressed);
}

void MainClass::DRAW()
{
	mainMenu->Draw();
}

void MainClass::FINALIZATOR()
{
}

MainClass::~MainClass(void)
{
}
