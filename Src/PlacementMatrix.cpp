#include "PlacementMatrix.h"


PlacementMatrix::PlacementMatrix(void)
{
}
PlacementMatrix::PlacementMatrix(IInput* input,ITexture* textureExplo,ITexture* P4Ship,ITexture* P3Ship,ITexture* P2Ship,ITexture* P1Ship,IBitmapFont* font, 
	bool isFriend,bool isCanShot,ITexture* textureSelection, ITexture* textureSea,Size cellSize,
	Position pos,Size size, State state,Player* ownerPlayer):matrix
	(isFriend,isCanShot,textureSelection,textureSea,cellSize,pos,size, state,ownerPlayer = NULL)
{
	_listOfShip = new vector<Ship*>(0);
	_input = input;
	_textureExplo = textureExplo;
	_font = font;
	_4PShip = P4Ship;
	_3PShip = P3Ship;
	_2PShip = P2Ship;
	_1PShip = P1Ship;
	uint x,y;
	_4PShip->GetDimensions(x,y);
	_4PShip->SetFrameSize(x/4,y/2);
	_3PShip->GetDimensions(x,y);
	_3PShip->SetFrameSize(x/3,y/2);
	_2PShip->GetDimensions(x,y);
	_2PShip->SetFrameSize(x/2,y/2);
	_1PShip->GetDimensions(x,y);
	_1PShip->SetFrameSize(x/1,y/2);
	_countOf4PSh = 1;
	_countOf3PSh = 2;
	_countOf2PSh = 3;
	_countOf1PSh = 4;
	_isRightFilled = false;
	_cursorShip = new ShipOnCursor(this,Position(0,0,0),Size(0,0),DEACTIVE,_textureExplo,NULL,0);
	IInput* _input;
}

void PlacementMatrix::Draw()
{
	char* _string = new char[3];

	_4PShip->Draw2D(_position.GetX(),_position.GetY()+_size.GetHeight()+50,_cellSize.GetWidth(),_cellSize.GetHeight(),0,0);
	_4PShip->Draw2D(_position.GetX()+_cellSize.GetWidth(),_position.GetY()+_size.GetHeight()+50,_cellSize.GetWidth(),_cellSize.GetHeight(),0,1);
	_4PShip->Draw2D(_position.GetX()+_cellSize.GetWidth()*2,_position.GetY()+_size.GetHeight()+50,_cellSize.GetWidth(),_cellSize.GetHeight(),0,2);
	_4PShip->Draw2D(_position.GetX()+_cellSize.GetWidth()*3,_position.GetY()+_size.GetHeight()+50,_cellSize.GetWidth(),_cellSize.GetHeight(),0,3);
	itoa(_countOf4PSh,_string,10);
	_string[1] = _string[0];
	_string[0] = 'x';
	_string[2] = '\0';
	_font->Draw2D(_position.GetX()+_cellSize.GetWidth()*4+25,_position.GetY()+_size.GetHeight()+50,_string,TColor4(100,120,230,250));

	_1PShip->Draw2D(_position.GetX()+192,_position.GetY()+_size.GetHeight()+50,_cellSize.GetWidth()*1,_cellSize.GetHeight(),0,0);
	itoa(_countOf1PSh,_string,10);
	_string[1] = _string[0];
	_string[0] = 'x';
	_string[2] = '\0';
	_font->Draw2D(_position.GetX()+192+_cellSize.GetWidth()*1+25,_position.GetY()+_size.GetHeight()+50,_string,TColor4(100,120,230,250));

	_3PShip->Draw2D(_position.GetX(),_position.GetY()+_size.GetHeight()+150,_cellSize.GetWidth(),_cellSize.GetHeight(),0,0);
	_3PShip->Draw2D(_position.GetX()+_cellSize.GetWidth(),_position.GetY()+_size.GetHeight()+150,_cellSize.GetWidth(),_cellSize.GetHeight(),0,1);
	_3PShip->Draw2D(_position.GetX()+_cellSize.GetWidth()*2,_position.GetY()+_size.GetHeight()+150,_cellSize.GetWidth(),_cellSize.GetHeight(),0,2);
	itoa(_countOf3PSh,_string,10);
	_string[1] = _string[0];
	_string[0] = 'x';
	_string[2] = '\0';
	_font->Draw2D(_position.GetX()+_cellSize.GetWidth()*3+25,_position.GetY()+_size.GetHeight()+150,_string,TColor4(100,120,230,250));

	_2PShip->Draw2D(_position.GetX()+192,_position.GetY()+_size.GetHeight()+150,_cellSize.GetWidth()*1,_cellSize.GetHeight(),0,0);
	_2PShip->Draw2D(_position.GetX()+192+_cellSize.GetWidth(),_position.GetY()+_size.GetHeight()+150,_cellSize.GetWidth()*1,_cellSize.GetHeight(),0,1);
	itoa(_countOf2PSh,_string,10);
	_string[1] = _string[0];
	_string[0] = 'x';
	_string[2] = '\0';
	_font->Draw2D(_position.GetX()+192+_cellSize.GetWidth()*2+25,_position.GetY()+_size.GetHeight()+150,_string,TColor4(100,120,230,250));
	matrix::Draw();
	if(_cursorShip->GetState() == DEACTIVE)
	{
	}
	else
	{
		_cursorShip->Draw();
	}
	
	
}

void PlacementMatrix::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if((_countOf4PSh == 0)&&(_countOf3PSh == 0)&&(_countOf2PSh == 0)&&(_countOf1PSh == 0))
		_isRightFilled = true;
	else
		_isRightFilled = false;

	_input->GetMouseStates(mouseState);
	isLeftMouseClicked = isClicked;
	isLeftMousePressed = isPressed;
	if(mouseState.bRightButton)

			{
				isRightMousePressed = true;

			}
			else
				if (isRightMousePressed)
				{
					isRightMouseClicked = true;
					isRightMousePressed = false;
				}
				else
				{
					isRightMouseClicked = false;
					isRightMousePressed = false;
				}
				
	if(_cursorShip->GetState() == DEACTIVE)
	{
			matrix::Process(mousePos,isClicked,isPressed,_char);
		if(_state == NORMALSTATE)
		{//4
			if((_position.GetX()<=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+50<=mousePos.GetY())&&
				(_position.GetX()+_cellSize.GetWidth()*4>=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+50+_cellSize.GetHeight()>=mousePos.GetY())&&
				(isClicked)&&(_countOf4PSh>0))
			{
				_cursorShip = new ShipOnCursor(this,Position(mousePos.GetX(),mousePos.GetY(),0),Size(_cellSize.GetWidth()*4,_cellSize.GetHeight()),NORMALSTATE,_textureExplo,_4PShip,4);
			}
			//3
			if((_position.GetX()<=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+150<=mousePos.GetY())&&
				(_position.GetX()+_cellSize.GetWidth()*3>=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+150+_cellSize.GetHeight()>=mousePos.GetY())&&
				(isClicked)&&(_countOf3PSh>0))
			{
				_cursorShip = new ShipOnCursor(this,Position(mousePos.GetX(),mousePos.GetY(),0),Size(_cellSize.GetWidth()*3,_cellSize.GetHeight()),NORMALSTATE,_textureExplo,_3PShip,3);
			}
			//2
			if((_position.GetX()+192<=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+150<=mousePos.GetY())&&
				(_position.GetX()+_cellSize.GetWidth()*2+192>=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+150+_cellSize.GetHeight()>=mousePos.GetY())&&
				(isClicked)&&(_countOf2PSh>0))
			{
				_cursorShip = new ShipOnCursor(this,Position(mousePos.GetX(),mousePos.GetY(),0),Size(_cellSize.GetWidth()*2,_cellSize.GetHeight()),NORMALSTATE,_textureExplo,_2PShip,2);
			}
			//1
			if((_position.GetX()+192<=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+50<=mousePos.GetY())&&
				(_position.GetX()+_cellSize.GetWidth()*1+192>=mousePos.GetX())&&
				(_position.GetY()+_size.GetHeight()+50+_cellSize.GetHeight()>=mousePos.GetY())&&
				(isClicked)&&(_countOf1PSh>0))
			{
				_cursorShip = new ShipOnCursor(this,Position(mousePos.GetX(),mousePos.GetY(),0),Size(_cellSize.GetWidth()*1,_cellSize.GetHeight()),NORMALSTATE,_textureExplo,_1PShip,1);
			}
		}
	}
	else
	{
		matrix::Process(mousePos,isClicked,isPressed,_char);
		_cursorShip->Process(mousePos,isLeftMouseClicked,isLeftMousePressed,isRightMouseClicked,isRightMousePressed);
		
	}
}

State PlacementMatrix::GetState()
{
	return _state;
}
void PlacementMatrix::SetState(State state)
{
	_state = state;
}
PlacementMatrix::~PlacementMatrix(void)
{
}
