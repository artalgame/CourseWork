#pragma once
#include "menuclass.h"
#include "Player.h"

class SinglePlayerMenu :
	public MenuClass
{
private:
	Player* _currentPlayer;
	vector<Player*>* _players;
public:
	bool _isPlayerShootedYet;
	SinglePlayerMenu(void);
	SinglePlayerMenu(vector<Player*>* players, Player* player, ITexture* fonImage, IMusic* fonMusic,Position pos, Size size,State state);

	void Shoot(void);

	//overrided methods
	void Draw(void);
	void Process(Position mousePos,bool isClicked,bool isPressed,char* _char=NULL);

	//methds for a encapsulation
	Player* GetCurrentPlayer(void);
	vector<Player*>* GetPlayers(void);
	Player* GetPlayer(int index);

	void AddPlayer(Player* newPlayer);
	void SetCurrentPlayer(Player* player);
	void SetPlayers(vector<Player*>* players);

	~SinglePlayerMenu(void);
};

