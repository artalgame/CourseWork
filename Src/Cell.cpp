#include "matrix.h"
#include "Cell.h"

//Constructor
Cell::Cell(void)
{
	_textureSea = NULL;
	_textureSelection = NULL;
}

Cell::Cell(matrix* ownerMatrix,ITexture* textureSea, ITexture* textureSelection,
	Position pos, Size size, State state):DrawObject(pos, size, state)
{
	_textureSea = textureSea;
	_textureSelection = textureSelection;
	if(_textureSea != NULL)
	{
		uint width, height;
		_textureSea->GetDimensions(width, height);
		_textureSea->SetFrameSize(width/3, height);
		_textureSelection->GetDimensions(width,height);
		_textureSelection->SetFrameSize(width/2, height/2);
	}
	_ownerMatrix = ownerMatrix;
	_isShoted = false;
	_isNearShip = false;
	_isShipCell = false;
}

//Overrided method
bool Cell::GetShot()
{
	if(!_isShoted)
	{
	_isShoted = true;
	_ownerMatrix->_isWasAttacked = true;
	//
	return true;
	}
	else
		return false;
}
void Cell::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if((_state != DEACTIVE)&&(_textureSea != NULL))
	{
		if((mousePos.GetX()>=_position.GetX())
			&& (mousePos.GetX()<=_position.GetX()+_size.GetWidth())
			&& (mousePos.GetY()>=_position.GetY())
			&& (mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
		{
			if(isClicked)//((isClicked || isPressed))
			{
				_state = PRESSED;
				if(_ownerMatrix->_isCanShot)
					if(_isShoted == false)
					{
						_isShoted = true;
						//_ownerMatrix->_isCanShot = false;
					}
			}
			else 
				_state = UNDERCURSOR;
		}
		else
		{			
			_state = NORMALSTATE;
		}
	}
}

void Cell::Draw()
{
	if ((_state != DEACTIVE)&&(_textureSea != NULL))
	{
		/*if (_state != ACTIVE)
		{*/
		if(!_isShoted)
		{
			if (_state == PRESSED)
			{
				if (_textureSea != NULL)

					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(), 1);

				if (_textureSelection != NULL)
					if((_ownerMatrix->_isCanShot))
						_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(),1);
					else
						_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), _position.GetAngle(),3);
			}
			else
				if (_state == UNDERCURSOR)
				{

					if (_textureSea != NULL)
						_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), 0, 1);
					if(_textureSelection != NULL)
						if((_ownerMatrix->_isCanShot))
							_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), 0,0);
						else
							_textureSelection->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), 0,2);
				}
				else
					_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), 0, 0);

		}
		else
		{
			_textureSea->Draw2D(_position.GetX(), _position.GetY(), _size.GetWidth(), _size.GetHeight(), 0, 2);
		}
	}
}

//Methods for a encapsulation
ITexture* Cell::Get_TextureSea(void)
{
	return _textureSea;
}

ITexture* Cell::Get_TextureSelection(void)
{
	return _textureSelection;
}

State Cell::GetState(void)
{
	return _state;
}

void Cell::Set_TextureSea(ITexture* textureSea)
{
	_textureSea = textureSea;
}

void Cell::Set_TextureSelection(ITexture* textureSelection)
{
	_textureSelection = textureSelection;
}


void Cell::SetState(State state)
{
	_state = state;
}

void Cell::SetOwnerMatrix(matrix* ownerMatrix)
{
	_ownerMatrix = ownerMatrix;
}

matrix* Cell::GetOwnerMatrix()
{
   return _ownerMatrix;
}

string* Cell::ToString()
{
	char* st = new char[10];
	string* answ = new string("Cell:");
	*answ+=(*_position.ToString());
	*answ+='#';
	*answ+=(*_size.ToString());
	*answ+='#';
	itoa(_state,st,10);
	*answ+=_state;
	*answ+='/';

	if(_isShoted)
		*answ+='t';
  	else
	    *answ+='f';
	*answ+='/';
	if(_isNearShip)
		*answ+='t';
	else
		*answ+='f';
	*answ+='/';
	if(_isShipCell)
		*answ+='t';
	else
		*answ+='f';
	return answ;
}
void Cell::FromString(string* s)
{
   char* st = new char[10];
   s->erase(0,4);//delete Cell:
   int ind =s->find_first_of("S");
   string pos;
   for(int i =0;i<ind;i++)
   {
	   pos+=(*s)[i];
   }
   _position.FromString(&pos);
   ind = s->find_last_of('#');
   string size;
   for(int i =0;i<ind;i++)
   {
	   size+=(*s)[i];
   }
   s->erase(0,ind);
   if((*s)[0]=='t')
	   _isShoted = true;
   else 
	   _isShoted = false;
   if((*s)[2] == 't')
	   _isNearShip = true;
   else
	   _isNearShip = false;
   if((*s)[4] == 't')
	   _isShipCell = true;
   else
	   _isShipCell = false;

}
//Destructor
Cell::~Cell()
{
}