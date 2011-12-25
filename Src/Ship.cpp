#include <time.h>
#include "matrix.h"
#include "Ship.h"


Ship::Ship(void)
{
}

Ship::Ship(ITexture* shipTex,ITexture* textureExplo,int countOfPalubs, 
	Position pos,Size size, State state,bool isHorizontal, bool isDied):DrawObject(pos,size,state)
{
	_isWasAttacked = false;
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
	/*for(int i =0;i<_countOfPalubs;i++)
	{
		if(_isHorizontal)
			_shipCells[i] ->SetPosition(Position(_position.GetX()+(_size.GetWidth()/_countOfPalubs+edgeHor)*i,_position.GetY(),0));
		else
			_shipCells[i] -> SetPosition(Position(_position.GetX(),_position.GetY()+(_size.GetHeight()+edgeVert)*i,90));
	}*/
	int count = 0;
	for(int i=0; i<GetCountOfPalubs();i++)
		if(_shipCells[i]->_isExplo)
		{
			count++;
		}
	if(count == GetCountOfPalubs())
	{
		_isDied = true;
		DrawContur();
	}
	if(_isWasAttacked)
	{
		if(_isDied)
			if(_shipCells[0]->GetOwnerMatrix()->_isFriend)			
				SoundClass::Play(3);
			else
			SoundClass::Play(2);
		else
		if(!_shipCells[0]->GetOwnerMatrix()->_isFriend)
			SoundClass::Play(1);
	}
}
void Ship::DrawContur()
{
	for(int k =0;k<GetCountOfPalubs();k++)
	{
		matrix* Matrix = GetCell(0)->GetOwnerMatrix();
		Cell*** _cellMatrix = Matrix->_cellMatrix;
		if(!GetIsHorizontal())
		{
			
			int i =GetPosition().GetX()+k;
			int j =GetPosition().GetY();
			if((k == 0)&&(i-1>=0))
			{
				_cellMatrix[i-1][j]->_isShoted = true;
				if(j-1>=0)
					_cellMatrix[i-1][j-1]->_isShoted = true;
				if(j+1<10)
					_cellMatrix[i-1][j+1]->_isShoted = true;
			}
			if((k == GetCountOfPalubs()-1)&&(i+1<10))
			{
				_cellMatrix[i+1][j]->_isShoted = true;
				if(j-1>=0)
					_cellMatrix[i+1][j-1]->_isShoted = true;
				if(j+1<10)
					_cellMatrix[i+1][j+1]->_isShoted = true;
			}
			if((j-1>=0))
				_cellMatrix[i][j-1]->_isShoted = true;
			if((j+1<10))
				_cellMatrix[i][j+1]->_isShoted = true;
		}
		else
		{
			int i =GetPosition().GetX();
			int j =GetPosition().GetY()+k;

			
			if((k == 0)&&(j-1>=0))
			{
				_cellMatrix[i][j-1]->_isShoted = true;
				if(i-1>=0)
					_cellMatrix[i-1][j-1]->_isShoted = true;
				if(i+1<10)
					_cellMatrix[i+1][j-1]->_isShoted = true;
			}
			if((k == GetCountOfPalubs()-1)&&(j+1<10))
			{
				_cellMatrix[i][j+1]->_isShoted = true;
				if(i-1>=0)
					_cellMatrix[i-1][j+1]->_isShoted = true;
				if(i+1<10)
					_cellMatrix[i+1][j+1]->_isShoted = true;
			}
			if((i-1>=0))
				_cellMatrix[i-1][j]->_isShoted = true;
			if((i+1<10))
				_cellMatrix[i+1][j]->_isShoted = true;
		}
	}
}

void Ship::SetPosition(Position pos)
{
	DrawObject::SetPosition(pos);
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
	SetPosition(_position);
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

string* Ship::ToString()
{
	string* answ = new string("Ship:");
	if(_isHorizontal)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';
	if(_isDied)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';
	char* count = new char[10];
	itoa(_countOfPalubs,count,10);
	*answ+=count;
	*answ+='/';
	char* hor = new char[10];
	itoa(edgeHor,hor,10);
	*answ+=hor;
	*answ+='/';
	char*vert = new char[10];
	itoa(edgeVert,vert,10);
	*answ+=vert;
	*answ+='/';
	if(_isWasAttacked)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';
	for(int i =0;i<_countOfPalubs;i++)
	{
		*answ+=*(_shipCells[i]->ToString());
		*answ=+'/';
	}
	return answ;
}
void Ship::FromString(string* s)
{
	s->erase(0,4);
	if((*s)[0] == 't')
	_isHorizontal = true;
	else _isHorizontal = false;
	s->erase(0,1);
	if((*s)[0] == 't')
		_isDied = true;
	else
		_isDied = false;
	s->erase(0,1);

	int ind = s->find_first_of('/');
	char* count = new char[10];
	s->copy(count,ind);
	_countOfPalubs = atoi(count);
	s->erase(0,ind);

	ind = s->find_first_of('/');
	char* hor = new char[10];
	s->copy(hor,ind);
	edgeHor = atoi(hor);
	s->erase(0,ind);

	ind = s->find_first_of('/');
	char* vert= new char[10];
	s->copy(vert,ind);
	edgeVert = atoi(vert);
	s->erase(0,ind);

	if((*s)[0] == 't')
		_isWasAttacked = true;
	else
		_isWasAttacked = false;

	s->erase(0,1);
	for(int i =0; i<_countOfPalubs;i++)
	{
		ind = s->find_first_of('/');
		char* cell = new char[100];
		s->copy(cell,ind);
		_shipCells[i]->FromString(s);
		s->erase(0,ind);
	}

}
Ship::~Ship(void)
{
}
