#include "SinglePlayerMenu.h"


SinglePlayerMenu::SinglePlayerMenu(void):MenuClass()
{
	_players = NULL;
	_currentPlayer = NULL;
}

SinglePlayerMenu::SinglePlayerMenu(vector<Player*>* players, Player* currentPlayer, ITexture* fonImage, 
	IMusic* fonMusic,Position pos, Size size,State state):MenuClass(fonImage, fonMusic, pos, size, state)
{
	_players = players;
	_currentPlayer = currentPlayer;
}


void SinglePlayerMenu::Shoot(void)
{
	
}

void SinglePlayerMenu::Draw(void)
{
	MenuClass::Draw();
	
	_currentPlayer->Draw();
	
	for (int i = 0; i < _players->size(); i++)
	{
		_players->operator[](i)->Draw();
	}
}

void SinglePlayerMenu::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	MenuClass::Process(mousePos, isClicked, isPressed, _char);
	_currentPlayer->Process(mousePos,isClicked,isPressed,_char);
	
	for (int i = 0; i < _players->size(); i++)
	{
		_players->operator[](i)->Process(mousePos,isClicked,isPressed,_char);
	}
}

Player* SinglePlayerMenu::GetCurrentPlayer(void)
{
	return _currentPlayer;
}

vector<Player*>* SinglePlayerMenu::GetPlayers(void)
{
	return _players;
}

Player* SinglePlayerMenu::GetPlayer(int index)
{
	Player* res = NULL;
	if ((index < 0) && (index >= _players->size()))
	{
		res = (*_players)[index];
	}
	
	return res;
}

void SinglePlayerMenu::AddPlayer(Player* newPlayer)
{
	if (newPlayer != NULL)
		_players->push_back(newPlayer);
}

void SinglePlayerMenu::SetCurrentPlayer(Player* player)
{
	_currentPlayer = player;
}

void SinglePlayerMenu::SetPlayers(vector<Player*>* players)
{
	_players = players;
}

SinglePlayerMenu::~SinglePlayerMenu(void)
{
}
