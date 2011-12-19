#include "MenuEdit.h"

MenuEdit::MenuEdit(void):DrawObject()
{
	_backgroundImage = NULL;
	_text = "";
	_font = NULL;
	_inputCharCounter = 0;
	_color = new TColor4(0, 0, 0, 255);
	_isMarkered = false;
	_isWrited = true;
}

MenuEdit::MenuEdit(ITexture* backgroundImage, string text, IBitmapFont* font, IInput* input,  Position pos, Size size, State state, TColor4* color):DrawObject(pos, size, state)
{
	_backgroundImage = backgroundImage;
	_text = text;
	_font = font;
	_input = input;
	_color = color;
	_inputCharCounter = 0;
	_isMarkered = false;
	_isWrited = true;
}

void MenuEdit::Draw(void)
{
	if(_backgroundImage != NULL)
		_backgroundImage->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());

	if(_font != NULL)
	{
		uint x, y, x1, y1;
		_font->GetTextDimensions("|", x1, y1);
		if (_text.length() != 0)
			_font->GetTextDimensions(_text.c_str() ,x1,y1);
		if (((x1 + 2 * ((_text.length() > 0)?(x1 / _text.length()):0)) <= _size.GetWidth()) && (y1 <= _size.GetHeight()))
			_isWrited = true;
		else 
			_isWrited = false;

		x = _position.GetX()+(_size.GetWidth()-x1)/2;
		y = _position.GetY()+(_size.GetHeight()-y1)/2;

		//Output '|'marker
		if (_isMarkered && (_state == ACTIVE))
			_font->Draw2D(x + x1, y, "|", *_color); 

		_font->Draw2D(x,y, _text.c_str() , *_color,_position.GetAngle());
	}
}

void MenuEdit::Process(Position mousePos,bool isClicked,bool isPressed,char* _char)
{
	if(_state != DEACTIVE)
	{
		if((mousePos.GetX()>=_position.GetX())
			&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth())
			&&(mousePos.GetY()>=_position.GetY())
			&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
		{
			if(isClicked)
				_state = ACTIVE;
			else 
				if (_state != ACTIVE)
					_state = UNDERCURSOR;
		}
		else
		{
			if((_state == ACTIVE) && isClicked)
			{
				_state = NORMALSTATE;
			}
		}

		if(_state == ACTIVE)
		{
			++_inputCharCounter;
			if (_inputCharCounter == 5)
			{
				_inputCharCounter = 0;
				_isMarkered = !_isMarkered;
				bool keypressed;

				//Cheking Shifts
				bool isLShiftPressed, isRShiftPressed;
				_input->GetKey(KEY_LSHIFT, isLShiftPressed);
				_input->GetKey(KEY_RSHIFT, isRShiftPressed);

				//Delete symbol if backspase pressed
				_input->GetKey(KEY_BACKSPACE, keypressed);
				if (keypressed && (_text.length() != 0))
				{
					_text.pop_back();
					return;
				}

				//Space cheking 
				_input->GetKey(KEY_SPACE, keypressed);
				if (keypressed && _isWrited)
				{
					_text.push_back(' ');
					return;
				}

				int inpKey = 15;
				//Cheking letterd
				while ((inpKey <= 50) && !keypressed)
				{
					++inpKey;
					_input->GetKey((DGLE2::E_KEYBOARD_KEY_CODES)inpKey, keypressed);
				}

				
				uchar inpChar;
				_input->GetKeyName((DGLE2::E_KEYBOARD_KEY_CODES)inpKey, inpChar);
				if ((inpChar >= 65) && (inpChar <= 90) && _isWrited)
					_text.push_back((char)((isLShiftPressed || isRShiftPressed)?toupper(inpChar):tolower(inpChar)));
			}
		}
	}
}

//Methods for an encapsulation
ITexture* MenuEdit::Get_BackgroundImage(void)
{
	return _backgroundImage;
}

string* MenuEdit::Get_Text(void)
{
	return &_text;
}

IBitmapFont* MenuEdit::Get_Font(void)
{
	return _font;
}

IInput* MenuEdit::Get_Input(void)
{
	return _input;
}

TColor4* MenuEdit::Get_Color(void)
{
	return _color;
}

State MenuEdit::GetState(void)
{
	return _state;
}

void MenuEdit::Set_BackgroundImage(ITexture* backgroundImage)
{
	_backgroundImage = backgroundImage;
}

void MenuEdit::Set_Text(string text)
{
	_text = text;
}

void MenuEdit::Set_Font(IBitmapFont* font)
{
	_font = font;
}

void MenuEdit::Set_Input(IInput* input)
{
	_input = input;
}

void MenuEdit::Set_Color(TColor4* color)
{
	_color = color;
}

void MenuEdit::SetState(State state)
{
	_state = state;
}

MenuEdit::~MenuEdit(void)
{
}