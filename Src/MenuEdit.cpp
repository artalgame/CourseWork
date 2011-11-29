/*		KEY_ESCAPE			= 0x01,
KEY_TAB				= 0x0F,
KEY_GRAVE			= 0x29,
KEY_CAPSLOCK		= 0x3A,
KEY_BACKSPACE		= 0x0E,
KEY_RETURN			= 0x1C,
KEY_SPACE			= 0x39,
KEY_SLASH			= 0x35,
KEY_BACKSLASH		= 0x2B,
KEY_SYSRQ			= 0xB7,
KEY_SCROLL			= 0x46,
KEY_PAUSE			= 0xC5,
KEY_INSERT			= 0xD2,
KEY_DELETE			= 0xD3,
KEY_HOME			= 0xC7,
KEY_END				= 0xCF,
KEY_PGUP			= 0xC9,
KEY_PGDN			= 0xD1,
KEY_LSHIFT			= 0x2A,
KEY_RSHIFT			= 0x36,
KEY_LALT			= 0x38,
KEY_RALT			= 0xB8,
KEY_LWIN			= 0xDB,
KEY_RWIN			= 0xDC,
KEY_LCONTROL		= 0x1D,
KEY_RCONTROL		= 0x9D,
KEY_UP				= 0xC8,
KEY_RIGHT			= 0xCD,
KEY_LEFT			= 0xCB,
KEY_DOWN			= 0xD0,
KEY_1				= 0x02,
KEY_2				= 0x03,
KEY_3				= 0x04,
KEY_4				= 0x05,
KEY_5				= 0x06,
KEY_6				= 0x07,
KEY_7				= 0x08,
KEY_8				= 0x09,
KEY_9				= 0x0A,
KEY_0				= 0x0B,
KEY_F1				= 0x3B,
KEY_F2				= 0x3C,
KEY_F3				= 0x3D,
KEY_F4				= 0x3E,
KEY_F5				= 0x3F,
KEY_F6				= 0x40,
KEY_F7				= 0x41,
KEY_F8				= 0x42,
KEY_F9				= 0x43,
KEY_F10				= 0x44,
KEY_F11				= 0x57,
KEY_F12				= 0x58,
KEY_Q				= 0x10,
KEY_W				= 0x11,
KEY_E				= 0x12,
KEY_R				= 0x13,
KEY_T				= 0x14,
KEY_Y				= 0x15,
KEY_U				= 0x16,
KEY_I				= 0x17,
KEY_O				= 0x18,
KEY_P				= 0x19,
KEY_A				= 0x1E,
KEY_S				= 0x1F,
KEY_D				= 0x20,
KEY_F				= 0x21,
KEY_G				= 0x22,
KEY_H				= 0x23,
KEY_J				= 0x24,
KEY_K				= 0x25,
KEY_L				= 0x26,
KEY_Z				= 0x2C,
KEY_X				= 0x2D,
KEY_C				= 0x2E,
KEY_V				= 0x2F,
KEY_B				= 0x30,
KEY_N				= 0x31,
KEY_M				= 0x32,
KEY_MINUS			= 0x0C,
KEY_PLUS			= 0x0D,
KEY_LBRACKET		= 0x1A,
KEY_RBRACKET		= 0x1B,
KEY_SEMICOLON		= 0x27,
KEY_APOSTROPHE		= 0x28,
KEY_COMMA			= 0x33,
KEY_PERIOD			= 0x34,
KEY_NUMPAD0			= 0x52,
KEY_NUMPAD1			= 0x4F,
KEY_NUMPAD2			= 0x50,
KEY_NUMPAD3			= 0x51,
KEY_NUMPAD4			= 0x4B,
KEY_NUMPAD5			= 0x4C,
KEY_NUMPAD6			= 0x4D,
KEY_NUMPAD7			= 0x47,
KEY_NUMPAD8			= 0x48,
KEY_NUMPAD9			= 0x49,
KEY_NUMPADPERIOD	= 0x53,
KEY_NUMPADENTER		= 0x9C,
KEY_NUMPADSTAR		= 0x37,
KEY_NUMPADPLUS		= 0x4E,
KEY_NUMPADMINUS		= 0x4A,
KEY_NUMPADSLASH		= 0xB5,
KEY_NUMLOCK			= 0x45,*/

#include "MenuEdit.h"

MenuEdit::MenuEdit(void):DrawObject()
{
	_backgroundImage = NULL;
	_text = "";
	_font = NULL;
	_inputCharCounter = 0;
	_isMarkered = false;
}

MenuEdit::MenuEdit(ITexture* backgroundImage, string text, IBitmapFont* font, IInput* input,  Position pos, Size size, State state):DrawObject(pos, size, state)
{
	_backgroundImage = backgroundImage;
	_text = text;
	_font = font;
	_input = input;
	_inputCharCounter = 0;
	_isMarkered = false;
}

void MenuEdit::Draw(void)
{
	if(_backgroundImage != NULL)
		_backgroundImage->Draw2D(_position.GetX(),_position.GetY(),_size.GetWidth(),_size.GetHeight(),_position.GetAngle());

	if(_font != NULL)
	{
		TColor4 color = TColor4(0,0,0,255);
		uint x, y;
		_font->GetTextDimensions(_text.c_str() ,x,y);
		x = _position.GetX()+(_size.GetWidth()-x)/2;
		y = _position.GetY()+(_size.GetHeight()-y)/2;
		_font->Draw2D(x,y,_text.c_str(),color,_position.GetAngle());
	}
}

void MenuEdit::Process(Position mousePos,bool isClicked,bool isPressed)
{
	if(_state != DEACTIVE)
	{
		if((mousePos.GetX()>=_position.GetX())
			&&(mousePos.GetX()<=_position.GetX()+_size.GetWidth())
			&&(mousePos.GetY()>=_position.GetY())
			&&(mousePos.GetY()<=_position.GetY()+_size.GetHeight()))
		{
			if(isClicked)
			{
				_state = ACTIVE;
			}
		}
		else
		{
			if((_state == ACTIVE) && isClicked)
			{
				_state = NORMALSTATE;
				if (_isMarkered)
				{
					_text.pop_back();
					_isMarkered = false;
				}
			}
		}
		if(_state == ACTIVE)
		{
			++_inputCharCounter;
			if (_inputCharCounter == 5)
			{
				/*//Output '|'marker
				_isMarkered = !_isMarkered;
				if (_isMarkered)
					_text.push_back('|');
				else
					_text.pop_back();	
				*/

				//Cheking Shifts
				bool isLShiftPressed, isRShiftPressed;
				_input->GetKey(KEY_LSHIFT, isLShiftPressed);
				_input->GetKey(KEY_RSHIFT, isRShiftPressed);

				int inpKey = 0;
				bool keypressed;

				//Delete symbol if backspase pressed
				_input->GetKey(KEY_BACKSPACE, keypressed);
				if (keypressed && (_text.length() != 0))
					_text.pop_back();

				//Chering letterd and space
				for (inpKey = 16; inpKey <= 50; inpKey++)
				{
					_input->GetKey((DGLE2::E_KEYBOARD_KEY_CODES)inpKey, keypressed);
					if (keypressed)
						break;
				}

				//42 - LeftShift
				if ((inpKey != 51) && (inpKey != 42))
				{
					uchar inpChar;
					_input->GetKeyName((DGLE2::E_KEYBOARD_KEY_CODES)inpKey, inpChar);
					_text.push_back((char)((isLShiftPressed || isRShiftPressed)?toupper(inpChar):tolower(inpChar)));
				}
				_inputCharCounter = 0;
			}
		}
	}
}

//Methods for an encapsulation
ITexture* MenuEdit::Get_BackgroundImage(void)
{
	return _backgroundImage;
}

string MenuEdit::Get_Text(void)
{
	return _text;
}

IBitmapFont* MenuEdit::Get_Font(void)
{
	return _font;
}

IInput* MenuEdit::Get_Input(void)
{
	return _input;
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

void MenuEdit::SetState(State state)
{
	_state = state;
}

MenuEdit::~MenuEdit(void)
{
}