#include "StdAfx.h"
#include "Parametr.h"
#include "size.h"

Parametr::Parametr()
{
	_size=Size();
	_weight=0;
}
Parametr::Parametr(Size size,int weight)
{
	_size=size;
	_weight=weight;
}
Parametr::Parametr(int height, int width, int weight)
{
	Size size(height, width);
	_size=size;
	_weight=weight;
}
Size Parametr::GetSize()
{
	return _size;
}
int Parametr::GetWeight()
{
	return _weight;
}
void Parametr::SetWeight(int weight)
{
	if(weight<0)
		weight=0;
	_weight=weight;
}
