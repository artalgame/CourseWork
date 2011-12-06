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
	isMouseClicked=false;
	isMousePressed=false;
	_gameState = MAIN_MENU;
}

void MainClass::LOADER()
{
	IBitmapFont* font;
	ITexture* tex;

	pResourceManager->Load("..\\Data\\music\\FonMusic1.mp3",(IEngBaseObj*&)pFonMusic);
	//pResourceManager->Load("..\\Data\\sounds\\buttons\\click.mp3",(IEngBaseObj*&)click);
	//pResourceManager->Load("..\\Data\\sounds\\buttons\\CursorOn.mp3",(IEngBaseObj*&)cursorOn);
	click = NULL;
	cursorOn = NULL;
	pResourceManager->Load("..\\Data\\textures\\fon1.jpg",(IEngBaseObj*&)tex);

	mainMenu = new MainMenuClass(tex,pFonMusic,Position(0,0,0),Size(800,600),NORMALSTATE,this);
	pResourceManager->Load("..\\Data\\textures\\buttons\\single_player.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,180,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"single player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\multiPlayer.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,250,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"multi player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\settings.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,320,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"settings"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\quit.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,390,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"exit"));

	pResourceManager->Load("..\\Data\\fonts\\font1.dft",(IEngBaseObj*&)font);

	pResourceManager->Load("..\\Data\\textures\\buttons\\droplist_button.png",(IEngBaseObj*&)tex);
	MenuButton* newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), tex, click, 
		cursorOn, NORMALSTATE, "droplist teams");

	pResourceManager->Load("..\\Data\\textures\\edit_field.jpg",(IEngBaseObj*&)tex);
	MenuDropList* newMenuDropList = new MenuDropList(Position(400,200, 0), Size(180, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, tex);

	pResourceManager->Load("..\\Data\\textures\\label.png",(IEngBaseObj*&)tex);
	newLabel =new  MenuLabel("DroplistLabel1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),tex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	
	newLabel =new  MenuLabel("DroplistLabel2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),tex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	
	newLabel =new  MenuLabel("DroplistLabel3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),tex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	
	pResourceManager->Load("..\\Data\\textures\\Game\\Water.jpg",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new Cell(tex, NULL, Position(20, 20, 0), Size(20, 20), NORMALSTATE));
	
	//mainMenu->AddElement(newMenuDropList);
	mainMenu->PlayMusic(true);
	
}

void MainClass::PROCESS()
{
	TMouseStates mouseState;


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
		

		switch (_gameState)
		{
		case MAIN_MENU:
			mainMenu->Process(mousePos,isMouseClicked,isMousePressed);
			break;
		case EXIT:
			pEngineCore->QuitEngine();
			break;
		}
}

void MainClass::DRAW()
{
	switch (_gameState)
		{
		case MAIN_MENU:
		mainMenu->Draw();
			break;
		}

	
}

void MainClass::FINALIZATOR()
{
}

MainClass::~MainClass(void)
{
}
