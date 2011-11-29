#include <Windows.h>
#include"DGLE2.h"
#include"DGLE2_EXT.h"
#include"MenuButton.h"
#include"MenuClass.h"
#include"MenuLabel.h"
#include"MenuEdit.h"

using namespace DGLE2;
using namespace std;

void CALLBACK Init(void *pParametr);
void CALLBACK Process(void *pParametr);
void CALLBACK Render(void *pParametr);
void CALLBACK Free(void *pParametr);


IEngineCore *pEngineCore = NULL;
IResourceManager *pResourceManager = NULL;
IRender2D *pRender2D = NULL;
IRender *pRender = NULL;
IInput *pInput = NULL;
ITexture *pExitButton = NULL;
IMusic *pFonMusic = NULL;
IMusic* click;
IMusic* cursorOn;
MenuButton button;
MenuClass mainMenu;
MenuLabel newLabel;
MenuEdit newEdit;

bool isMouseClicked = false;
bool isMousePressed = false;

bool bIsGame = false;
int uiCounter = 0;

ENG_DYNAMIC_FUNC
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	if(GetEngine("DGLE2.dll", pEngineCore))
	{
		if(SUCCEEDED(pEngineCore->InitializeEngine(
			NULL, "SeaBattle", TEngWindow(800, 600, false), 33, EIF_CATCH_UNHANDLED)))
		{
			pEngineCore->AddProcedure(EPT_INIT, &Init);
			pEngineCore->AddProcedure(EPT_PROCESS, &Process);
			pEngineCore->AddProcedure(EPT_RENDER, &Render);
			pEngineCore->AddProcedure(EPT_FREE, &Free);
			pEngineCore->StartEngine();
			FreeEngine();
		}
		else
			MessageBoxA(NULL,"Couldn't inicialize!", "SeaBattle", MB_OK | MB_ICONERROR);
	}
	else
		MessageBoxA(NULL,"Couldn't load \"DGLE2.dll\"!", "Tutorial", MB_OK | MB_ICONERROR);
	return 0;
}

void ProcessTitle()
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

		mainMenu.Process(Position(mouseState.iX,mouseState.iY,0),isMouseClicked,isMousePressed);
		if(mainMenu.GetElement(3)->GetState() == PRESSED)
		{
			pEngineCore->QuitEngine();
		}
}

void RenderTitle()
{
	mainMenu.Draw();
}

void ProcessGame()
{
}

void RenderGame()
{
}

void CALLBACK Init(void *pParametr)
{
	IBitmapFont* font;

	pEngineCore->GetSubSystem(ESS_RESOURCE_MANAGER, (IEngineSubSystem *&)pResourceManager);
	pEngineCore->GetSubSystem(ESS_RENDER, (IEngineSubSystem *&)pRender);
	pEngineCore->GetSubSystem(ESS_INPUT, (IEngineSubSystem *&)pInput);

	pRender->GetRender2D(pRender2D);

	pResourceManager->Load("..\\Data\\music\\FonMusic2.mp3",(IEngBaseObj*&)pFonMusic);
	pResourceManager->Load("..\\Data\\sounds\\buttons\\click.mp3",(IEngBaseObj*&)click);
	pResourceManager->Load("..\\Data\\sounds\\buttons\\CursorOn.mp3",(IEngBaseObj*&)cursorOn);
	pResourceManager->Load("..\\Data\\textures\\fon1.jpg",(IEngBaseObj*&)pExitButton);

	mainMenu = MenuClass(pExitButton,pFonMusic,Position(0,0,0),Size(800,600),NORMALSTATE);
	pResourceManager->Load("..\\Data\\textures\\buttons\\singlePlayerBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu.AddElement(new MenuButton(Position(50,50,0),Size(64,64),pExitButton,click,cursorOn,NORMALSTATE,"single player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\singlePlayerBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu.AddElement(new MenuButton(Position(150,150,0),Size(64,64),pExitButton,click,cursorOn,NORMALSTATE,"Great button"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\multiPlayerBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu.AddElement(new MenuButton(Position(150,50,0),Size(64,64),pExitButton,click,cursorOn,DEACTIVE,"multi player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\settingBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu.AddElement(new MenuButton(Position(250,50,0),Size(64,64),pExitButton,click,cursorOn,DEACTIVE,"settings"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\exitBut.jpg",(IEngBaseObj*&)pExitButton);
	mainMenu.AddElement(new MenuButton(Position(350,50,0),Size(64,64),pExitButton,click,cursorOn,NORMALSTATE,"exit"));

	pResourceManager->Load("..\\Data\\fonts\\font1.dft",(IEngBaseObj*&)font);
	newLabel = MenuLabel("Label",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),TColor4(48,100),pExitButton,Position(300,300,0),Size(300,100),NORMALSTATE);
	mainMenu.AddElement(&newLabel);

	newEdit = MenuEdit(pExitButton, "", font, pInput, Position(100, 100, 0), Size(200, 30), NORMALSTATE);
	mainMenu.AddElement(&newEdit);

	mainMenu.PlayMusic(true);
}

void CALLBACK Render(void *pParametr)
{
	pRender2D->Begin2D();
	if(!bIsGame)
		RenderTitle();
	else
		RenderGame();
	pRender2D->End2D();
}

void CALLBACK Process(void *pParametr)
{
	if(bIsGame)
		ProcessGame();
	else
		ProcessTitle();

	bool key_pressed;
	pInput->GetKey(KEY_ESCAPE, key_pressed);
	if(key_pressed) pEngineCore->QuitEngine();

	uiCounter++;
}


void CALLBACK Free(void *pParametr)
{

}

