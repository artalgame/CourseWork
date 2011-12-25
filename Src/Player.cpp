#include "Player.h"


Player::Player(void)
{
	_isCanShot = true;
}

Player::Player(int numberOfTeam, matrix* matrix, string* name,vector<Ship*>* listOfShip,Position pos, Size size,State state,
	int countOfSlip,int countOfKills,int difficultyStage,int countOfHit,bool isCanShot, bool isFriend):DrawObject(pos, size,state)
{
	_numberOfTeam = numberOfTeam;
	_matrix = matrix;
	_name = name;
	_listOfShip = listOfShip;
	_difficultyStage = difficultyStage;
	_countOfSlip = countOfSlip;
	_countOfKills= countOfKills;
	_countOfHit = countOfHit;
	_isCanShot = isCanShot;
	_isFriend = isFriend;
	_isDied = false;
	_isWasAttacked = false;
	_isShipWasAttacked = false;
	for(int i =0;i<10;i++)
		for(int j =0;j<10;j++)
			_matrix->_cellMatrix[i][j]->SetOwnerMatrix(_matrix);
}
void Player::Draw()
{
	if(!_isDied)
	{
		_matrix->Draw();
	}
}

void Player::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if(!_isDied)
	{
		_attackedCell = NULL;
		_attackedShip = NULL;
		_matrix->Process(mousePos,isClicked,isPressed,_char);
		if((_isWasAttacked == false)&&(_matrix->_isWasAttacked))
		{
			_attackedCell = _matrix->_cellUnderCursorOrPressed;
			_isWasAttacked = _matrix->_isWasAttacked;
		}
		int count = 0;
		for(int i =0;i<_listOfShip->size();i++)
		{
			(*_listOfShip)[i]->Process(mousePos,isClicked,isPressed);
			if((*_listOfShip)[i]->_isWasAttacked)
			{
				_isShipWasAttacked = true;
				_isWasAttacked = true;
				_attackedShip = (*_listOfShip)[i];
			}
			if((*_listOfShip)[i]->GetIsDied())
				count++;
		}
		if(count == 10)
		{
			_isDied = true;
			ResetAttacked();
		}
	}
}

void Player::ResetAttacked()
{
	_matrix->_isWasAttacked = false;
	for(int i =0;i<_listOfShip->size();i++)
	{
		(*_listOfShip)[i]->_isWasAttacked = false;
	}
	_isShipWasAttacked = false;
	_isWasAttacked = false;
}
State Player::GetState()
{
	return _state;
}

void Player::MakeShot(vector<Player*>* players)
{
	vector<Player*>* foePlayers = new vector<Player*>(0);
	Player* foe;
	for(int i=0;i<players->size();i++)
	{
		if(((*players)[i]->_numberOfTeam !=_numberOfTeam)&&(!(*players)[i]->_isDied))
		{
			(*foePlayers).push_back((*players)[i]);
		}
	}
	while(true)
	{
		switch(_difficultyStage)
		{
		case 2:
			foe = MakeShotByStage2(foePlayers);
			break;
		default:
			foe = MakeShotByStage1(foePlayers);
			break;
		}
		foe->Update();
		if(foe->_isWasAttacked)
		{
			if(foe->_isShipWasAttacked)
			{
				foe->ResetAttacked();
				this->MakeShot(players);
				return;
			}
			else
			{
				return;
			}
		}
	}
}

Player* Player::MakeShotByStage2(vector<Player*>* foePlayers)
{
	int x,y;
	Position pos;

	for(int k=foePlayers->size()-1;k>=0;k--)
	{
		vector<Ship*>* foeShips = (*foePlayers)[k]->_listOfShip;
		for(int l = 0; l<foeShips->size();l++)
			if(!(*foeShips)[l]->GetIsDied())
			{		
				pos = (*foeShips)[l]->GetPosition();
				for(int i =0;i<(*foeShips)[l]->GetCountOfPalubs()-1;i++)
				{
					if((*foeShips)[l]->_shipCells[i]->_isExplo)
					{
						if((*foeShips)[l]->_shipCells[i+1]->_isExplo)
						{
							if(!(*foeShips)[l]->GetIsHorizontal())
							{
								x = pos.GetX()+i-1;
								y = pos.GetY();
								if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
								{
									return (*foePlayers)[k];
								}
								x = pos.GetX()+i+2;
								y = pos.GetY();
								if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
								{
									return (*foePlayers)[k];
								}
							}
							else
							{
								x = pos.GetX();
								y = pos.GetY()+i-1;
								if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
								{
									return (*foePlayers)[k];
								}
								x = pos.GetX();
								y = pos.GetY()+i+2;
								if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
								{
									return (*foePlayers)[k];
								}
							}
						}
						else
						{
							x = pos.GetX()+i-1;
							y = pos.GetY();
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}
							x = pos.GetX()+i+1;
							y = pos.GetY();
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}

							x = pos.GetX();
							y = pos.GetY()+i-1;
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}
							x = pos.GetX();
							y = pos.GetY()+i+1;
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}
						}
					}
				}
				int i = (*foeShips)[l]->GetCountOfPalubs()-1;

				if((*foeShips)[l]->_shipCells[i]->_isExplo)
				{
					        x = pos.GetX()+i-1;
							y = pos.GetY();
							
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}
							x = pos.GetX()+i+1;
							y = pos.GetY();
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}

							x = pos.GetX();
							y = pos.GetY()+i-1;
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}
							x = pos.GetX();
							y = pos.GetY()+i+1;
							if((CheckXandY(x,y))&&((*foePlayers)[k]->_matrix->_cellMatrix[x][y]->GetShot()))
							{
								return (*foePlayers)[k];
							}
				}
			}
	}
	return MakeShotByStage1(foePlayers);
}
bool Player::CheckXandY(int x, int y)
{
	if((x>=0)&&
	   (y>=0)&&
	   (x<10)&&
	   (y<10))
	   return true;
	else return false;
}
Player* Player::MakeShotByStage1(vector<Player*>* foePlayers)
{

	int i = rand()%foePlayers->size();
	int x,y;
	while(true)
	{
		x = rand()%10;
		y = rand()%10;
		if((*foePlayers)[i]->_matrix->_cellMatrix[x][y]->GetShot())
		{
			return (*foePlayers)[i];

		}
	}
}

void Player::Update()
{
	_attackedCell = NULL;
	_attackedShip = NULL;
	if((_isWasAttacked == false)&&(_matrix->_isWasAttacked))
	{
		_attackedCell = _matrix->_cellUnderCursorOrPressed;
		_isWasAttacked = _matrix->_isWasAttacked;
	}
	int count = 0;
	for(int i =0;i<_listOfShip->size();i++)
	{
		if((*_listOfShip)[i]->_isWasAttacked)
		{
			_isShipWasAttacked = true;
			_isWasAttacked = true;
			_attackedShip = (*_listOfShip)[i];
		}
		if((*_listOfShip)[i]->GetIsDied())
			count++;
	}
	if(count == 10)
	{
		_isDied = true;
		ResetAttacked();
	}
}
void Player::SetState(State state)
{
	_state = state;
}

string* Player::ToString()
{
	string* answ = new string("Player:");
	*answ+=*_name;
	*answ+='/';

	char* stage = new char[10];
	itoa(_difficultyStage,stage,10);
	*answ+=stage;
	*answ+='/';

	char* countSlip = new char[10];
	itoa(_countOfSlip,countSlip,10);
	*answ+=countSlip;
	*answ+='/';

	char* countKills = new char[10];
	itoa(_countOfKills,countKills,10);
	*answ+=countKills;
	*answ+='/';
    
	char* countHit = new char[10];
	itoa(_countOfHit,countHit,10);
	*answ+=countHit;
	*answ+='/';

	char* numberTeam = new char[10];
	itoa(_numberOfTeam,numberTeam,10);
	*answ+=countKills;
	*answ+='/';

	if(_isCanShot)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';

	if(_isFriend)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';

	if(_isWasAttacked)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';

	if(_isShipWasAttacked)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';

	if(_isDied)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';
	*answ+=*_matrix->ToString();

	for(int i=0;i<10;i++)
	{
		*answ+=*(*_listOfShip)[i]->ToString();
		*answ+='/';
	}
	return answ;
}
void Player::FromString(string* s)
{
	s->erase(0,6);

	int ind = s->find_first_of('/');
	char* name = new char[50];
	s->copy(name,ind);
	 _name = new string(name);
	s->erase(0,ind);

	ind = s->find_first_of('/');
	char* stage = new char[10];
	s->copy(stage,ind);
	 _difficultyStage = atoi(stage);
	s->erase(0,ind);

	ind = s->find_first_of('/');
	char* countSlip = new char[10];
	s->copy(countSlip,ind);
	 _countOfSlip = atoi(countSlip);
	s->erase(0,ind);
	
	ind = s->find_first_of('/');
	char* countKills = new char[10];
	s->copy(countKills,ind);
	 _countOfKills = atoi(countKills);
	s->erase(0,ind);

	ind = s->find_first_of('/');
	char* countHit = new char[10];
	s->copy(countHit,ind);
	 _countOfHit = atoi(countHit);
	s->erase(0,ind);

	ind = s->find_first_of('/');
	char* numberTeam = new char[10];
	s->copy(numberTeam,ind);
	 _numberOfTeam = atoi(numberTeam);
	s->erase(0,ind);
	
	if((*s)[0] == 't')
		_isCanShot = true;
	else
		_isCanShot = false;
	s->erase(0,1);

	
	if((*s)[0] == 't')
		_isFriend = true;
	else
		_isFriend = false;
	s->erase(0,1);

	
	if((*s)[0] == 't')
		_isWasAttacked = true;
	else
		_isWasAttacked = false;
	s->erase(0,1);
    
	if((*s)[0] == 't')
		_isShipWasAttacked = true;
	else
		_isShipWasAttacked = false;
	s->erase(0,1);

	if((*s)[0] == 't')
		_isDied = true;
	else
		_isDied = false;
	s->erase(0,1);


	ind = s->find_first_of('/');
	char* matrix = new char[1000];
	s->copy(matrix,ind);
	_matrix->FromString(new string(matrix));
	s->erase(0,ind);

	for(int i=0;i<10;i++)
	{
	    ind = s->find_first_of('/');
	    char* ship = new char[300];
		(*_listOfShip)[i]->FromString(new string(ship));
		s->erase(0,ind);
	}
}
Player::~Player(void)
{
}
