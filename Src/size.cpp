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
string* Size::ToString()
{
	char* w = new char[10];
	char* h = new char[10];
	itoa(_width,w,10);
	itoa(_height,h,10);
	string* answ = new string("Size:");
    *answ+=*w;
	*answ+='#';
	*answ+=*h;
	return answ;	
}
void Size::FromString(string* s)
{
    char* w = new char[10];
	char* h = new char[10];
	s->erase(0,4);//delete "Size"
	int i = s->find('#');
	s->copy(w,i);
	_width = atoi(w);
	s->erase(0,i+1);
	s->copy(h,0);
	_height=atoi(h);
}


