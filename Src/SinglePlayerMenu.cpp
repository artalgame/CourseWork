#include "SinglePlayerMenu.h"


SinglePlayerMenu::SinglePlayerMenu(void):MenuClass()
{
	_players = NULL;
	_currentPlayer = NULL;
}

SinglePlayerMenu::SinglePlayerMenu(vector<Player*>* players, Player* currentPlayer, ITexture* fonImage, 
	IMusic* fonMusic,Position pos, Size size,State state):MenuClass(fonImage, fonMusic, pos, size, state)
{
	_isPlayerShootedYet = false;
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
	
	if(!_isPlayerShootedYet)
	{
		for (int i = 0; i < _players->size(); i++)
		{
			_players->operator[](i)->ResetAttacked();
		}
		for (int i = 0; i < _players->size(); i++)
		{
			_players->operator[](i)->Process(mousePos,isClicked,isPressed,_char);
			if(((*_players)[i]->_isWasAttacked)&&(!(*_players)[i]->_isShipWasAttacked))
			{
				_isPlayerShootedYet = true;
			}
		}
	}
	else
	{
		if(_objectList[0]->GetState() == PRESSED)
		{
			_isPlayerShootedYet = false;
			_players->push_back(_currentPlayer);
			for (int i = 0; i < _players->size()-1; i++)
			{
				if(!(*_players)[i]->_isDied)
					_players->operator[](i)->MakeShot(_players);
			}

			_players->pop_back();
			for (int i = 0; i < _players->size(); i++)
			{
				_players->operator[](i)->Process(mousePos,false,false,_char);
			}
			return;
		}
		for (int i = 0; i < _players->size(); i++)
		{
			_players->operator[](i)->Process(mousePos,false,false,_char);
		}
	}
	int countOfEnemy = 0;
	for(int i = 0; i<_players->size();i++)
	{
		if((!(*_players)[i]->_isDied)&&(!(*_players)[i]->_isFriend))
			countOfEnemy++;
	}
	if(countOfEnemy == 0)
	{
		_currentPlayer->_matrix->SetPosition(Position(100,100,0));
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
