#include <Windows.h>
#include"DGLE2.h"
#include"DGLE2_EXT.h"
#include"MenuButton.h"
#include"MenuClass.h"
#include"MenuLabel.h"
#include"MenuDropList.h"
#include"MainClass.h"

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
MainClass main;



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

void CALLBACK Init(void *pParametr)
{
	
	pEngineCore->GetSubSystem(ESS_RESOURCE_MANAGER, (IEngineSubSystem *&)pResourceManager);
	pEngineCore->GetSubSystem(ESS_RENDER, (IEngineSubSystem *&)pRender);
	pEngineCore->GetSubSystem(ESS_INPUT, (IEngineSubSystem *&)pInput);

	pRender->GetRender2D(pRender2D);

	main = MainClass(pEngineCore, pResourceManager, pRender2D, pRender, pInput);
	main.LOADER();
}

void CALLBACK Render(void *pParametr)
{
	pRender2D->Begin2D();
	main.DRAW();
	pRender2D->End2D();
}

void CALLBACK Process(void *pParametr)
{
	main.PROCESS();
}


void CALLBACK Free(void *pParametr)
{
	main.FINALIZATOR();
}

