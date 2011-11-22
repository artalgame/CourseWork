#pragma once
#include "size.h"
#include "Position.h"
#include "DGLE2.h"
#include"DGLE2_EXT.h"
typedef enum
{
	NORMALSTATE, UNDERCURSOR,PRESSED, DEACTIVE, ACTIVE
}State;
class DrawObject
{
protected:
    Size _size;//size of object
	Position _position;//position on the screen
	State _state;
public:
	DrawObject(void);
	DrawObject(Position pos, Size size,State state);

	Size GetSize();
	Position GetPosition();

	void SetSize(Size size);
	void SetPosition(Position pos);	

	virtual void Draw() = 0;
	virtual void Process(Position mousePos,bool isClicked,bool isPressed) = 0;
    virtual void SetState(State state)=0;
	virtual State GetState()=0;
	~DrawObject(void);
};

