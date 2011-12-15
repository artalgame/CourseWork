#include "Player.h"
#include "matrix.h"


matrix::matrix(void)
{	
}
matrix::matrix(bool isFriend,bool isCanShot,ITexture* textureSelection, ITexture* textureSea,Size cellSize,Position pos, 
	Size size, State state,Player* ownerPlayer):DrawObject(pos, size, state)
{
	_isFriend = isFriend;
	if(_isFriend)
		_isCanShot = false;
	else _isCanShot = isCanShot;

	_textureSelection = textureSelection;
	_textureSea = textureSea;
	_cellSize = cellSize;
	_cellMatrix = new Cell**[10];
	_ownerPlayer = ownerPlayer;
	for(int i=0; i<10; i++)
		_cellMatrix[i] = new Cell*[10];

	edgeHor = 5;
	edgeVert = 5;
	for(int i=0; i<10; i++)
		for(int j = 0; j<10; j++)
		{
			if(i == 0 )
				edgeVert = 0;
			else 
				edgeVert = 5;
			if(j == 0 )
				edgeHor = 0;
			else 
				edgeHor = 5;
			_cellMatrix[i][j] = new Cell(this,_textureSea,_textureSelection,Position(pos.GetX()+
				(_cellSize.GetWidth()+edgeHor)*j,pos.GetY()+(_cellSize.GetHeight()+edgeVert)*i,0),_cellSize,NORMALSTATE);
		}
}
void matrix::Draw()
{
	for(int i=0; i<10; i++)
		for(int j = 0; j<10; j++)
			_cellMatrix[i][j]->Draw();
}

void matrix::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	State st = NORMALSTATE;
	_cellUnderCursorOrPressed = NULL;
	for(int i=0; i<10; i++)
		for(int j = 0; j<10; j++)
		{			
			_cellMatrix[i][j]->Process(mousePos,isClicked,isPressed);
			if(_cellMatrix[i][j]->GetState() != NORMALSTATE)
			{
				_cellUnderCursorOrPressed = _cellMatrix[i][j];
				_cellPosition = Position(i,j,0);
				st = _cellMatrix[i][j]->GetState();
			}
		}
		_state = st;
}

State matrix::GetState()
{
	return _state;
}

void matrix::SetState(State state)
{
	_state = state;
}

bool matrix::AddShip(Ship* ship)
{
	bool isGood = true;
	for(int i =0;i<ship->GetCountOfPalubs();i++)
	{
		if(!ship->GetIsHorizontal())
		{
			if((ship->GetPosition().GetX()+i>=10)
				||(_cellMatrix[ship->GetPosition().GetX()+i][ship->GetPosition().GetY()]->_isNearShip)
				||(_cellMatrix[ship->GetPosition().GetX()+i][ship->GetPosition().GetY()]->_isShipCell))
				return false;
		}
		else
			if((ship->GetPosition().GetY()+i>=10)
				||(_cellMatrix[ship->GetPosition().GetX()][ship->GetPosition().GetY()+i]->_isNearShip)
				||(_cellMatrix[ship->GetPosition().GetX()][ship->GetPosition().GetY()+i]->_isShipCell))
				return false;
	}

	for(int k =0;k<ship->GetCountOfPalubs();k++)
	{

		if(!ship->GetIsHorizontal())
		{
			int i =ship->GetPosition().GetX()+k;
			int j =ship->GetPosition().GetY();
			_cellMatrix[i][j] = ship->GetCell(k);
			_cellMatrix[i][j]->SetOwnerMatrix(this);

			_cellMatrix[i][j]->SetPosition(
				Position(_position.GetX()+(_cellSize.GetWidth()+edgeHor)*j,_position.GetY()+(_cellSize.GetHeight()+edgeVert)*i,ship->GetPosition().GetAngle()));
			_cellMatrix[i][j]->Set_TextureSea(_textureSea);
			_cellMatrix[i][j]->Set_TextureSelection(_textureSelection);
			if((k == 0)&&(i-1>=0))
			{
				_cellMatrix[i-1][j]->_isNearShip = true;
				if(j-1>=0)
					_cellMatrix[i-1][j-1]->_isNearShip = true;
				if(j+1<10)
					_cellMatrix[i-1][j+1]->_isNearShip = true;
			}
			if((k == ship->GetCountOfPalubs()-1)&&(i+1<10))
			{
				_cellMatrix[i+1][j]->_isNearShip = true;
				if(j-1>=0)
					_cellMatrix[i+1][j-1]->_isNearShip = true;
				if(j+1<10)
					_cellMatrix[i+1][j+1]->_isNearShip = true;
			}
			if((j-1>=0))
				_cellMatrix[i][j-1]->_isNearShip = true;
			if((j+1<10))
				_cellMatrix[i][j+1]->_isNearShip = true;
		}
		else
		{
			int i =ship->GetPosition().GetX();
			int j =ship->GetPosition().GetY()+k;

			_cellMatrix[i][j] = ship->GetCell(k);
			_cellMatrix[i][j]->SetOwnerMatrix(this);

			_cellMatrix[i][j]->SetPosition(
				Position(_position.GetX()+(_cellSize.GetWidth()+edgeHor)*j,_position.GetY()+(_cellSize.GetHeight()+edgeVert)*i,ship->GetPosition().GetAngle()));
			_cellMatrix[i][j]->Set_TextureSea(_textureSea);
			_cellMatrix[i][j]->Set_TextureSelection(_textureSelection);
			if((k == 0)&&(j-1>=0))
			{
				_cellMatrix[i][j-1]->_isNearShip = true;
				if(i-1>=0)
					_cellMatrix[i-1][j-1]->_isNearShip = true;
				if(i+1<10)
					_cellMatrix[i+1][j-1]->_isNearShip = true;
			}
			if((k == ship->GetCountOfPalubs()-1)&&(j+1<10))
			{
				_cellMatrix[i][j+1]->_isNearShip = true;
				if(i-1>=0)
					_cellMatrix[i-1][j+1]->_isNearShip = true;
				if(i+1<10)
					_cellMatrix[i+1][j+1]->_isNearShip = true;
			}
			if((i-1>=0))
				_cellMatrix[i-1][j]->_isNearShip = true;
			if((i+1<10))
				_cellMatrix[i+1][j]->_isNearShip = true;
		}
	}
	return true;
}

matrix* matrix::GenretateMatrix(ITexture* _4PShip,ITexture* _3PShip,ITexture* _2PShip,ITexture* _1PShip,ITexture* _textureExplo)
{
	int cOfShip = 10;
	int currentShip = 4;
	int cOf4 = 1;
	int cOf3 = 2;
	int cOf2 = 3;
	int cOf1 = 4;
	int i;
	int j;
	bool isHor;
	matrix* mat = new matrix(true,false,_textureSelection,_textureSea,_cellSize,Position(0,0,0),
		Size(_cellSize.GetWidth()*10+edgeHor*9,_cellSize.GetHeight()*10+edgeVert*9),NORMALSTATE,NULL);

	Ship* ship;
	
	while(cOfShip != 0)
	{
		i = rand()%10;
		j = rand()%10;
		if((!mat->_cellMatrix[i][j]->_isShipCell)&&(!mat->_cellMatrix[i][j]->_isNearShip))
		{
			switch(currentShip)
			{
			case 1:
				isHor = rand() % 2;
				ship = new Ship(_1PShip,_textureExplo,1,Position(i,j,90*isHor),Size(_cellSize.GetWidth(),_cellSize.GetHeight()),NORMALSTATE,isHor);
				break;
			case 2:
				isHor = rand() % 2;
				ship = new Ship(_2PShip,_textureExplo,2,Position(i,j,90*isHor),Size(_cellSize.GetWidth()*2,_cellSize.GetHeight()),NORMALSTATE,isHor);
				break;
			case 3:
				isHor = rand() % 2;
				ship = new Ship(_3PShip,_textureExplo,3,Position(i,j,90*isHor),Size(_cellSize.GetWidth()*3,_cellSize.GetHeight()),NORMALSTATE,isHor);
				break;
			case 4:
				isHor = rand() % 2;
				ship = new Ship(_4PShip,_textureExplo,4,Position(i,j,90*isHor),Size(_cellSize.GetWidth()*4,_cellSize.GetHeight()),NORMALSTATE,isHor);
				break;
			}
			if(mat->AddShip(ship))
			{
				cOfShip--;
				switch(currentShip)
				{
				case 1:
					cOf1--;
					break;
				case 2:
					cOf2==1?currentShip = 1:cOf2--;
					break;
				case 3:
					cOf3==1?currentShip = 2:cOf3--;
					break;
				case 4:
					cOf4==1?currentShip = 3:cOf2--;
					break;
				}
			}
		}
	}
	return mat;
}

matrix::~matrix(void)
{
}
