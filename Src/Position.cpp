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

string* Position::ToString()
{
	char* x = new char[10];
	char* y = new char[10];
	char* a = new char[10];
	itoa(_x,x,10);
	itoa(_y,y,10);
	itoa(_angle,a,10);
	string* answ = new string("Position:");
	*answ+=*x;
	*answ+='#';
	*answ+=*y;
	*answ+='#';
	*answ+=*a;
	return answ;
}
void Position::FromString(string* s)
{
	char* x = new char[10];
	char* y = new char[10];
	char* a = new char[10];
	s->erase(0,7);//delete "Position"
	int i = s->find('#');
	s->copy(x,i);
	_x = atoi(x);
	s->erase(0,i+1);
	i = s->find('#');
	s->copy(y,i);
	_y= atoi(y);
	s->erase(0,i+1);
	s->copy(a,s->length()-1);
	_angle = atoi(a);
}