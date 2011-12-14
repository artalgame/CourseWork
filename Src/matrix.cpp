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
	for(int i=0; i<10; i++)
		for(int j = 0; j<10; j++)
		{
			
			_cellMatrix[i][j]->Process(mousePos,isClicked,isPressed);
			if(_cellMatrix[i][j]->GetState() != NORMALSTATE)
			{
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

void matrix::AddShip(Ship* ship)
{
	for(int i =0;i<ship->GetCountOfPalubs();i++)
	{
		if(ship->GetIsHorizontal())
		{
			_cellMatrix[ship->GetPosition().GetX()+i][ship->GetPosition().GetY()] = ship->GetCell(i);
			_cellMatrix[ship->GetPosition().GetX()+i][ship->GetPosition().GetY()]->SetPosition(
				Position(_position.GetX()+(ship->GetPosition().GetX()+i)*_cellSize.GetWidth(),ship->GetPosition().GetY(),0));
			_cellMatrix[ship->GetPosition().GetX()+i][ship->GetPosition().GetY()]->SetSize(Size(_cellSize.GetWidth(),_cellSize.GetHeight()));
		}
		else
		{
			_cellMatrix[ship->GetPosition().GetX()][ship->GetPosition().GetY()+i] = ship->GetCell(i);
			_cellMatrix[ship->GetPosition().GetX()][ship->GetPosition().GetY()+i]->SetPosition(
				Position(_position.GetX(),ship->GetPosition().GetY()+(ship->GetPosition().GetY()+i)*_cellSize.GetHeight(),0));
			_cellMatrix[ship->GetPosition().GetX()+i][ship->GetPosition().GetY()]->SetSize(Size(_cellSize.GetWidth(),_cellSize.GetHeight()));
		}
	}
}

matrix::~matrix(void)
{
}
