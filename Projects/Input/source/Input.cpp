#define DllExport
#include "DllAPIs\Input.h"
#include "Input.h"

#define GetKeyCode(_LParam)			(unsigned short)((_LParam & 0x01ff0000) >> 16)
#define GetMouseXParam(_LParam)		(		  short)((_LParam & 0x0000ffff)		 )
#define GetMouseYParam(_LParam)		(		  short)((_LParam & 0xffff0000) >> 16)
#define GetMouseXButton(_WParam)	(		  short)((_WParam & 0xffff0000) >> 16)

bool Input::Init()
{
	PrintFuncEntry();

	for(int i = 0; i < Key::KeyMax; ++i)
	{
		Input::m_KeyActions[i] = Input::KeyAction(	[](Key _Key){	printf("Key Down: %i.\n", _Key);	},
													[](Key _Key){	printf("Key Up:   %i.\n", _Key);	}	);
	}
	for(int i = 0; i < MouseBtn::KeyMax; ++i)
	{
		Input::m_MouseBtnActions[i] = Input::MouseBtnAction([](MouseBtn _MouseBtn, short2 _MousePos){	printf("MouseBtn Down: %i.\n", _MouseBtn);	},
															[](MouseBtn _MouseBtn, short2 _MousePos){	printf("MouseBtn Up:   %i.\n", _MouseBtn);	}	);
	}

	Input::m_OnMouseMove = [](short2 _MousePos){};

	return true;
}

void Input::Terminate()
{
	PrintFuncEntry();
}

void Input::OnKeyDown(Key _Key)
{
	switch(_Key)
	{
	case Key::LCtrl:
	case Key::RCtrl: 	Input::m_KeyStates[(unsigned short)_Key] = true;
						Input::m_KeyActions[(unsigned short)_Key].OnKeyDown(_Key);
						Input::m_KeyStates[(unsigned short)Key::Ctrl] = true;
						Input::m_KeyActions[(unsigned short)Key::Ctrl].OnKeyDown(Key::Ctrl);	break;

	case Key::LShift:
	case Key::RShift: 	Input::m_KeyStates[(unsigned short)_Key] = true;
						Input::m_KeyActions[(unsigned short)_Key].OnKeyDown(_Key);
						Input::m_KeyStates[(unsigned short)Key::Shift] = true;
						Input::m_KeyActions[(unsigned short)Key::Shift].OnKeyDown(Key::Shift);	break;

	//case Key::LAlt:
	case Key::RAlt: 	Input::m_KeyStates[(unsigned short)_Key] = true;
						Input::m_KeyActions[(unsigned short)_Key].OnKeyDown(_Key);
						Input::m_KeyStates[(unsigned short)Key::Alt] = true;
						Input::m_KeyActions[(unsigned short)Key::Alt].OnKeyDown(Key::Alt);	break;

	default:
		if(_Key < Key::KeyMax)
		{
			Input::m_KeyStates[(unsigned short)_Key] = true;
			Input::m_KeyActions[(unsigned short)_Key].OnKeyDown(_Key);
		}
		break;
	}
}

void Input::OnKeyUp(Key _Key)
{
	switch(_Key)
	{
	case Key::LCtrl:
	case Key::RCtrl: 	Input::m_KeyStates[(unsigned short)_Key] = false;
						Input::m_KeyActions[(unsigned short)_Key].OnKeyUp(_Key);
						Input::m_KeyStates[(unsigned short)Key::Ctrl] = false;
						Input::m_KeyActions[(unsigned short)Key::Ctrl].OnKeyUp(Key::Ctrl);	break;

	case Key::LShift:
	case Key::RShift: 	Input::m_KeyStates[(unsigned short)_Key] = false;
						Input::m_KeyActions[(unsigned short)_Key].OnKeyUp(_Key);
						Input::m_KeyStates[(unsigned short)Key::Shift] = false;
						Input::m_KeyActions[(unsigned short)Key::Shift].OnKeyUp(Key::Shift);	break;

	//case Key::LAlt:
	case Key::RAlt: 	Input::m_KeyStates[(unsigned short)_Key] = false;
						Input::m_KeyActions[(unsigned short)_Key].OnKeyUp(_Key);
						Input::m_KeyStates[(unsigned short)Key::Alt] = false;
						Input::m_KeyActions[(unsigned short)Key::Alt].OnKeyUp(Key::Alt);	break;

	default:
		if(_Key < Key::KeyMax)
		{
			Input::m_KeyStates[(unsigned short)_Key] = false;
			Input::m_KeyActions[(unsigned short)_Key].OnKeyUp(_Key);
		}
		break;
	}
}

void Input::OnMouseBtnDown( MouseBtn _MouseBtn )
{
	Input::m_MouseBtnStates[(unsigned short)_MouseBtn] = true;
	Input::m_MouseBtnActions[(unsigned short)_MouseBtn].OnMouseBtnDown(_MouseBtn, Input::m_MousePos);
}

void Input::OnMouseBtnUp( MouseBtn _MouseBtn )
{
	Input::m_MouseBtnStates[(unsigned short)_MouseBtn] = false;
	Input::m_MouseBtnActions[(unsigned short)_MouseBtn].OnMouseBtnUp(_MouseBtn, Input::m_MousePos);
}

void Input::OnMouseMove(short2 _NewPos)
{
	Input::m_MousePos = _NewPos;
	Input::m_OnMouseMove(Input::m_MousePos);
}

bool Input::HandleMessage(HWND _HWND, UINT _Message, WPARAM _WParam, LPARAM _LParam)
{
	//printf("Message %i 0x%x.\n", _Message, _Message);

	switch(_Message)
	{
		// Keyboard Input.
		//										If it's not already down.
		case WM_SYSKEYDOWN:		
		case WM_KEYDOWN:	if(!Input::m_KeyStates[GetKeyCode(_LParam)])	Input::OnKeyDown((Key)GetKeyCode(_LParam));	return true;
		case WM_SYSKEYUP:		
		case WM_KEYUP:														Input::OnKeyUp((Key)GetKeyCode(_LParam));	return true;
		case WM_MOUSEMOVE:		Input::OnMouseMove(short2(GetMouseXParam(_LParam), GetMouseYParam(_LParam)));			return true;

		// Mouse Input.
		// Down.
		case WM_LBUTTONDOWN:	Input::OnMouseBtnDown(MouseBtn::Left);													return true;
		case WM_RBUTTONDOWN:	Input::OnMouseBtnDown(MouseBtn::Right);													return true;
		case WM_MBUTTONDOWN:	Input::OnMouseBtnDown(MouseBtn::Middle);												return true;
		case WM_XBUTTONDOWN:	if(GetMouseXButton(_WParam) == 1)	Input::OnMouseBtnDown(MouseBtn::Btn4);
								else								Input::OnMouseBtnDown(MouseBtn::Btn5);				return true;
		// Up.
		case WM_LBUTTONUP:		Input::OnMouseBtnUp(MouseBtn::Left);													return true;
		case WM_RBUTTONUP:		Input::OnMouseBtnUp(MouseBtn::Right);													return true;
		case WM_MBUTTONUP:		Input::OnMouseBtnUp(MouseBtn::Middle);													return true;
		case WM_XBUTTONUP:		if(GetMouseXButton(_WParam) == 1)	Input::OnMouseBtnUp(MouseBtn::Btn4);
								else								Input::OnMouseBtnUp(MouseBtn::Btn5);				return true;
	}

	return false;
}

void Input::SetKeyAction(Key _Key, std::function<void(Key)> _OnKeyDown, std::function<void(Key)> _OnKeyUp)
{
	if(_OnKeyDown)	Input::m_KeyActions[(unsigned short)_Key].OnKeyDown = _OnKeyDown;
	if(_OnKeyUp)	Input::m_KeyActions[(unsigned short)_Key].OnKeyUp = _OnKeyUp;
}

void Input::SetMouseBtnAction(MouseBtn _MouseBtn, std::function<void(MouseBtn, short2)> _OnMouseBtnDown, std::function<void(MouseBtn, short2)> _OnMouseBtnUp)
{
	if(_OnMouseBtnDown)	Input::m_MouseBtnActions[(unsigned short)_MouseBtn].OnMouseBtnDown = _OnMouseBtnDown;
	if(_OnMouseBtnUp)	Input::m_MouseBtnActions[(unsigned short)_MouseBtn].OnMouseBtnUp = _OnMouseBtnUp;
}

void Input::SetOnMouseMove(std::function<void(short2)> _OnMouseMove)
{
	Input::m_OnMouseMove = _OnMouseMove;
}

bool Input::GetKeyState(Key _Key)
{
	return m_KeyStates[(unsigned short)_Key];
}