//This struct determines weight, and size parameters of objects
#pragma once
struct Position
{
private:
	int _x, _y, _angle;
public:
	Position();
	Position(int x, int y, int angle);
	int GetX();
	int GetY();
	int GetAngle();

	void SetX(int x);
	void SetY(int y);
	void SetAngle(int angle);
};

