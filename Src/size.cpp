#include "size.h"

Size::Size()
{
	_width=0;
	_height=0;
}
Size::Size( int width, int height)
{
	_width=width;
	_height=height;
}
int Size::GetHeight()
{
	return _height;
}
int Size::GetWidth()
{
	return _width;
}
void Size::SetHeight(int height)
{
	_height=height;
}
void Size::SetWidth(int width)
{
	_width=width;
}


