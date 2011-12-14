#include "Player.h"


Player::Player(void)
{
	_isCanShot = false;
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
}
void Player::Draw()
{
}

void Player::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
}

State Player::GetState()
{
	return _state;
}

void Player::SetState(State state)
{
	_state = state;
}

Player::~Player(void)
{
}
