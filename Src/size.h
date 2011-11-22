// This struct servies for presenration of object's size 
#pragma once
struct Size
{
private:
	int _height;
	int _width;
public:
	Size();
	Size( int width,int height);
	int GetHeight();
	void SetHeight(int height);
	int GetWidth();
	void SetWidth(int width);
};

