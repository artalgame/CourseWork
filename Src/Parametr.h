//This struct determines weight, and size parameters of objects
#pragma once
#include "size.h"
struct Position
{
private:
	int _x, _y;
public:
	Position();
	Position(int x, int y);
	int GetX();
	int GetY();

	void SetX();
	void SetY();
};

