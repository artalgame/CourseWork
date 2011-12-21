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
	return MakeShotByStage1(foePlayers);
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

Player::~Player(void)
{
}
