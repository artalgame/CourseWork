#include "Position.h"

Position::Position()
{
	_x = 0;
	_y = 0;
	_angle = 0;
}

Position::Position(int x, int y, int angle)
{
	_x = x;
	_y = y;
	_angle = angle;
}

int Position::GetX()
{
	return _x;
}

int Position::GetY()
{
	return _y;
}

int Position::GetAngle()
{
	return _angle;
}

void Position::SetX(int x)
{
	_x = x;
}

void Position::SetY(int y)
{
	_y = y;
}

void Position::SetAngle(int angle)
{
	_angle = angle;
}
