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
	ITexture* LabelTex;
	ITexture* EditTex;
	ITexture* tex;
	ITexture* ButtonTex;
	ITexture* DropListButtonTex;
	ITexture* Fon1Tex;
	IMusic *Music;
	MenuDropList* newMenuDropList;
	MenuButton* newDPButton;

	//Begin of loading Main Menu
	pResourceManager->Load("..\\Data\\music\\FonMusic1.mp3",(IEngBaseObj*&)Music);
	pResourceManager->Load("..\\Data\\textures\\fon1.jpg",(IEngBaseObj*&)Fon1Tex);
	pResourceManager->Load("..\\Data\\fonts\\font1.dft",(IEngBaseObj*&)font);
	pResourceManager->Load("..\\Data\\textures\\buttons\\droplist_button.png",(IEngBaseObj*&)DropListButtonTex);
	pResourceManager->Load("..\\Data\\textures\\edit_field.jpg",(IEngBaseObj*&)EditTex);
	pResourceManager->Load("..\\Data\\textures\\label.png",(IEngBaseObj*&)LabelTex);
	//pResourceManager->Load("..\\Data\\sounds\\buttons\\click.mp3",(IEngBaseObj*&)click);
	//pResourceManager->Load("..\\Data\\sounds\\buttons\\CursorOn.mp3",(IEngBaseObj*&)cursorOn);
	click = NULL;
	cursorOn = NULL;
	

	mainMenu = new MainMenuClass(Fon1Tex,Music,Position(0,0,0),Size(800,600),NORMALSTATE,this);
	pResourceManager->Load("..\\Data\\textures\\buttons\\single_player.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,180,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"single player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\multiPlayer.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,250,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"multi player"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\settings.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,320,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"settings"));

	pResourceManager->Load("..\\Data\\textures\\buttons\\quit.png",(IEngBaseObj*&)tex);
	mainMenu->AddElement(new MenuButton(Position(300,390,0),Size(200,50),tex,click,cursorOn,NORMALSTATE,"exit"));

	
    
        mainMenu->PlayMusic(true);
	//Finish of loading MainMenu

    //Begin of loading PreSingleplayerMenu All objects MUST loaded in the order!!!!!!!!!!!
    pResourceManager->Load("..\\Data\\textures\\fon2.jpg",(IEngBaseObj*&)Fon1Tex);
	preSPMenu = new PreSingleplayerMenu(Fon1Tex,NULL,Position(0,0,0),Size(800,600),NORMALSTATE,this);
	
	//load BACK BUTTON
	pResourceManager->Load("..\\Data\\textures\\buttons\\back.png",(IEngBaseObj*&)tex);
	preSPMenu->AddElement(new MenuButton(Position(30,520,0),Size(256,64),tex,click,cursorOn,NORMALSTATE,"back"));
	//----------------

	//load START BUTTON
	pResourceManager->Load("..\\Data\\textures\\buttons\\start.png",(IEngBaseObj*&)tex);
	preSPMenu->AddElement(new MenuButton(Position(520,520,0),Size(256,64),tex,click,cursorOn,DEACTIVE,"start"));
	//----------------

	//Load matrix
	ITexture* sel, *sea, *_4s,*_3s,*_2s,*_1s,*explo;
	pResourceManager->Load("..\\Data\\textures\\selection.png",(IEngBaseObj*&)sel);
	pResourceManager->Load("..\\Data\\textures\\sea.jpg",(IEngBaseObj*&)sea);
	pResourceManager->Load("..\\Data\\textures\\ships\\4.png",(IEngBaseObj*&)_4s);
	pResourceManager->Load("..\\Data\\textures\\ships\\3.png",(IEngBaseObj*&)_3s);
		pResourceManager->Load("..\\Data\\textures\\ships\\2.png",(IEngBaseObj*&)_2s);
			pResourceManager->Load("..\\Data\\textures\\ships\\1.png",(IEngBaseObj*&)_1s);
	pResourceManager->Load("..\\Data\\textures\\explo.png",(IEngBaseObj*&)explo);
	PlacementMatrix* mat = new PlacementMatrix(pInput,explo,_4s,_3s,_2s,_1s,font,true,false,sel,sea,Size(25,25),Position(400,50,0),Size(250,250),NORMALSTATE,NULL);
	preSPMenu->AddElement(mat);
	//-----------
	//label Players
	newLabel =new  MenuLabel("Players",font,TColor4(0,0,0,255),TColor4(0,0,0,255),TColor4(0,0,0,255),
		TColor4(0,0,0, 255),NULL,Position(30,20,0),Size(150, 40),NORMALSTATE);
	preSPMenu->AddElement(newLabel);
	//!!!!!!!!!!!!!!!!!!!!!!!
	//Edit for Name
	MenuEdit* newEdit = new MenuEdit(EditTex,"Your Name",font,pInput,Position(30,70,0),Size(150,30),NORMALSTATE,
		new TColor4(0,0,0,255));
	preSPMenu->AddElement(newEdit);
	//+++++++++++++++

	//Load the fifth drop down
	newDPButton = new MenuButton(Position(550, 510, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(30,470, 0), Size(150, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("Close",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Easy)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Hard)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!

	//load the fourth dropdown
	newDPButton = new MenuButton(Position(550, 450, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(30,390, 0), Size(150, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);	
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("Close",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Easy)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Hard)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Load the third dropdown
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(30,310, 0), Size(150, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("Close",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Easy)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Hard)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Load the second dropdown
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(30,230, 0), Size(150, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("Close",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Easy)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Hard)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//Load the first dropdown
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(30,150, 0), Size(150, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("Close",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Easy)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("Comp(Hard)",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//label Team
	newLabel =new  MenuLabel("Team",font,TColor4(0,0,0,255),TColor4(0,0,0,255),TColor4(0,0,0,255),
		TColor4(0,0,0, 255),NULL,Position(230,20,0),Size(100, 40),NORMALSTATE);
	preSPMenu->AddElement(newLabel);
	//!!!!!!!!!!!!!!!!!!!!!!!
	
	
			//Load the six dropdown Team
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(230,470, 0), Size(100, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("4",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("5",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("6",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
			//Load the fifth dropdown Team
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(230,390, 0), Size(100, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("4",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("5",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("6",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			//Load the fourth dropdown Team
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(230,310, 0), Size(100, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("4",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("5",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("6",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			//Load the third dropdown Team
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(230,230, 0), Size(100, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("4",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("5",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("6",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			//Load the second dropdown Team
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(230,150, 0), Size(100, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("4",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("5",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("6",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Load the first dropdown Team
	newDPButton = new MenuButton(Position(550, 200, 0), Size(30, 30), DropListButtonTex, click, 
		cursorOn, NORMALSTATE, "droplist teams");
	newMenuDropList = new MenuDropList(Position(230,70, 0), Size(100, 30), NORMALSTATE, 
		TColor4(0,0,0,255), newDPButton, 0, font, EditTex);
	//Add Elements to new  dropList
	newLabel =new  MenuLabel("1",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("2",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("3",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("4",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("5",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);

	newLabel =new  MenuLabel("6",font,TColor4(0,0,0,255),TColor4(244,32,32,255),TColor4(75,9,166,255),
		TColor4(0,0,0, 255),LabelTex,Position(430,200,0),Size(150, 30),NORMALSTATE);
	newMenuDropList->AddNewElement(newLabel);
	//________________________________________
	preSPMenu->AddElement(newMenuDropList);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	//End of loading PreSingleplayerMenu

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
		case PRE_SINGLEPLAYER:
			preSPMenu->Process(mousePos,isMouseClicked,isMousePressed);
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
	case PRE_SINGLEPLAYER:
		preSPMenu->Draw();
		break;
	}


}

void MainClass::FINALIZATOR()
{
}

MainClass::~MainClass(void)
{
}
