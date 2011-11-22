#include "DrawObject.h"


DrawObject::DrawObject(void)
{
	_size = Size(0,0);
	_position = Position(0,0,0);
	_state = DEACTIVE;
}

DrawObject::DrawObject(Position pos, Size size, State state)
{
	_position = pos;
	_size = size;
	_state = state;
}

void DrawObject::SetPosition(Position pos)
{
	_position = pos;
}

void DrawObject::SetSize(Size size)
{
	_size = size;
}

Position DrawObject::GetPosition()
{
	return _position;
}

Size DrawObject::GetSize()
{
	return _size;
}
DrawObject::~DrawObject()
{
}