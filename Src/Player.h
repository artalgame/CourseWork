#pragma once
#include "drawobject.h"
#include "matrix.h"
#include "Ship.h"
#include "DGLE2.h"
#include"DGLE2_EXT.h"
using namespace DGLE2;
using namespace std;
class Player :
	public DrawObject
{
protected:	
	string* _name;
	int _difficultyStage;
	int _countOfSlip;
	int _countOfKills;
	int _countOfHit;
Player*	MakeShotByStage1(vector<Player*>* foePlayers);
Player*	MakeShotByStage2(vector<Player*>* foePlayers);
bool CheckXandY(int x, int y);//check if x and y lie in matrix
public:
	int _numberOfTeam;
	matrix* _matrix;
	Ship* _attackedShip;
	Cell* _attackedCell;
	vector<Ship*>* _listOfShip;
	bool _isCanShot;//use for Cell and signalize, if we can shot to this cell.Used only mouse under matrix
	bool _isFriend;
	bool _isWasAttacked;
	bool _isShipWasAttacked;
	bool _isDied;

	Player(void);
	Player(int numberOfTeam,matrix* matrix, string* name,vector<Ship*>* listOfShip,Position pos, Size size,State state,int countOfSlip = 0,int countOfKills = 0,int difficultyStage =0, 
		int countOfHit = 0,bool isCanShot = true, bool isFriend = false);
	void Draw();
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);
	State GetState();
	void SetState(State state);
	void ResetAttacked();
	bool MakeShot(vector<Player*>* players);
	void Update();
	string* ToString();
	void FromString(string* s);
	~Player(void);
};

