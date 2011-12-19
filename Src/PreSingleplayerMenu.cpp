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
	int common = 0;
	try
	{
		PlacementMatrix* t = (PlacementMatrix*)_objectList[2];
		if(!t->_isRightFilled)
			isAllRight = false;
		else
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
		PlacementMatrix* mat = (PlacementMatrix*)_objectList[2];//our Placement matrix
		common+=1;//count of players
		//mat->edgeHor = 7 - common;
		//mat->edgeVert = 7- common;
		mat->edgeHor = 3;
		mat->edgeVert = 3;
		//Size cellSize(30-(common)*3+3,30-(common)*3+3);
		Size cellSize(15,15);
		mat->_cellSize = cellSize;
		mat->SetPosition(Position(10,10,0));//position of our player
		MenuDropList* team = (MenuDropList*)_objectList[16];//team of player
		matrix* player_mat = new matrix(*mat);//player matrix
		player_mat->SetPosition(mat->GetPosition());//make lines beetwen cells
		Player* you = new Player(atoi(team->GetChoisedElement()->GetCaption()),player_mat,((MenuEdit*)_objectList[4])->Get_Text(),mat->_listOfShip,mat->GetPosition(),
			mat->GetSize(),mat->GetState(),0,0,0,0,true,true);
		MenuDropList* s1;
		MenuDropList* s2;
		Position matrixPos;
		vector<Player*>* players = new vector<Player*>(0);
		vector<Ship*>* ships = new vector<Ship*>(0); 
		bool isFriendly;
		bool isCanShot = true;
		int stage;
		for(int i = 11; i<16;i++)
		{
			s1 = (MenuDropList*)_objectList[i];//team of computer
			s2 = (MenuDropList*)_objectList[i-6];//stage of computer
			if(s2->GetChoisedElement()->GetCaption() != "Close")
			{
				
				matrix* m = mat->GenretateMatrix(mat->_4PShip,mat->_3PShip,mat->_2PShip,mat->_1PShip,mat->_textureExplo,&ships);
				m->_cellSize = cellSize;
				if(i-10<=2)
				{
					matrixPos = Position(250*(i-10)+10,10,0);
				}
				else
				{
					matrixPos = Position(250*(i-13)+10,310,0);
				}
				m->edgeHor = mat->edgeHor;
				m->edgeVert = mat->edgeVert;
				m->_cellSize = cellSize;
				m->SetPosition(matrixPos);
				if(s1->GetChoisedElement()->GetCaption() == team->GetChoisedElement()->GetCaption())
				{
					isFriendly = true;
					m->_isFriend = true;
					m->_isCanShot = false;
				}
				else
				{
					isFriendly = false;
					m->_isFriend = false;
					m->_isCanShot = true;
				}
				if(s2->GetChoisedElement()->GetCaption() =="Comp(Easy)")
					stage = 1;
				else
					stage = 2;
				Player* player = new Player(atoi(((MenuDropList*)_objectList[i])->GetChoisedElement()->GetCaption()),m,new string(s2->GetChoisedElement()->GetCaption()),
					ships,matrixPos,Size(300,300),NORMALSTATE,0,0,stage,0,isCanShot,isFriendly);
				players->push_back(player);
			}
		}
		_owner->SPMenu->SetCurrentPlayer(you);
		_owner->SPMenu->SetPlayers(players);
		_owner->_gameState = SINGLEPLAYER;
	}
}
PreSingleplayerMenu::~PreSingleplayerMenu(void)
{
}
