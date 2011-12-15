#include "PreSingleplayerMenu.h"
#include "MainClass.h"

PreSingleplayerMenu::PreSingleplayerMenu(void)
{
}
PreSingleplayerMenu::PreSingleplayerMenu(ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state,MainClass* owner):
MenuClass(fonImage,fonMusic,pos,size,state)
{
	_owner = owner;
}

void PreSingleplayerMenu::Draw()
{
	MenuClass::Draw();
}

void PreSingleplayerMenu::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	MenuClass::Process(mousePos,isClicked,isPressed, _char);
	//check - if we can to allow to press button START
	bool isAllRight = true;
	try
	{
	//	PlacementMatrix* t = (PlacementMatrix*)_objectList[2];
	//	if(!t->_isRightFilled)
	//		isAllRight = false;
	//	else
		{
			int kol =0;
			MenuDropList* tmp;
			for(int i = 5; i<10;i++)
			{
				tmp = (MenuDropList*)_objectList[i];
				if(tmp->GetChoisedElement()->GetCaption() == "Close")
					kol++;
			}
			if(kol == 5)
				isAllRight = false;
			else
			{
				tmp = (MenuDropList*)_objectList[16];//team of player
				MenuDropList* s1;
				MenuDropList* s2;
				int common = 0;
				int friendly = 0;
				for(int i = 11; i<16;i++)
				{
					s1 = (MenuDropList*)_objectList[i];//level of computer
					s2 = (MenuDropList*)_objectList[i-6];//stage of computer
					if(s2->GetChoisedElement()->GetCaption() != "Close")
					{
						if(s1->GetChoisedElement()->GetCaption() == tmp->GetChoisedElement()->GetCaption())
							friendly++;
						common++;
					}
				}
				if(common == friendly) isAllRight = false; 
			}
		}

		if(isAllRight)
		{
			if(_objectList[1]->GetState() == DEACTIVE)
			_objectList[1]->SetState(NORMALSTATE);
		}
		else
			_objectList[1]->SetState(DEACTIVE);
	}
	catch(int ex)
	{

	}

	//===============================================
	if(_objectList[0]->GetState() == PRESSED)
	{
		_owner->_gameState = MAIN_MENU;
	}
	if(_objectList[1]->GetState() == PRESSED)
	{
		_owner->_gameState = SINGLEPLAYER;
	}
}
PreSingleplayerMenu::~PreSingleplayerMenu(void)
{
}
