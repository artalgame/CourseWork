#include "Ship.h"


Ship::Ship(void)
{
}

Ship::Ship(ITexture* shipTex,ITexture* textureExplo,int countOfPalubs, 
	Position pos,Size size, State state,bool isHorizontal, bool isDied):DrawObject(pos,size,state)
{
	_isHorizontal = isHorizontal;
	_isDied = isDied;
	_shipTex = shipTex;
	_countOfPalubs = countOfPalubs;
	_textureExplo = textureExplo;
	_shipCells = new ShipCell*[4];
	int edgeHor = 0;
	int edgeVert = 0;
	for(int i =0;i<_countOfPalubs;i++)
	{
		if(_isHorizontal)
			_shipCells[i] = new ShipCell(i,NULL,this,_shipTex,_textureExplo,NULL,NULL,Position(pos.GetX()+size.GetWidth()/_countOfPalubs*i,pos.GetY(),0),Size(size.GetWidth()/_countOfPalubs,size.GetHeight()),NORMALSTATE);
		else
			_shipCells[i] = new ShipCell(i,NULL,this,_shipTex,_textureExplo,NULL,NULL,Position(pos.GetX(),pos.GetY()+size.GetHeight()*i,90),Size(size.GetWidth()/countOfPalubs,size.GetHeight()),NORMALSTATE);
	}
}

void Ship::Draw()
{
	for(int i=0;i<_countOfPalubs;i++)
		_shipCells[i]->Draw();
}

void Ship::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	for(int i =0;i<_countOfPalubs;i++)
	{
		if(_isHorizontal)
			_shipCells[i] ->SetPosition(Position(_position.GetX()+(_size.GetWidth()/_countOfPalubs+edgeHor)*i,_position.GetY(),0));
		else
			_shipCells[i] -> SetPosition(Position(_position.GetX(),_position.GetY()+(_size.GetHeight()+edgeVert)*i,90));
	}
}

State Ship::GetState()
{
	return _state;
}

void Ship::SetState(State state)
{
	_state = state;
}

bool Ship::GetIsDied()
{
	return _isDied;
}

void Ship::SetIsDied(bool isDied)
{
	_isDied = isDied;
}

bool Ship::GetIsHorizontal()
{
	return _isHorizontal;
}

void Ship::SetIsHorizontal(bool isHorizontal)
{
	_isHorizontal = isHorizontal;
}

int Ship::GetCountOfPalubs()
{
	return _countOfPalubs;
}

void Ship::SetCountOfPalubs(int count)
{
	_countOfPalubs = count;
}

ShipCell* Ship::GetCell(int index)
{
	return _shipCells[index];
}

Ship::~Ship(void)
{
}