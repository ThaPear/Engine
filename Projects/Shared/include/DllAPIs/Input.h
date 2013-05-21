#pragma once

#define DllByLib "Input.lib"
#	include "DllAPI.h"
#undef DllByLib

namespace Input
{
	StartDllFuncs(
		DllFunc(Input, bool, Init, DllArgs(),
		DllFunc(Input, void, Terminate, DllArgs(),

		// Returns true if the message was handled.
		DllFunc(Input, bool, HandleMessage, DllArgs(HWND _HWND, UINT _Message, WPARAM _WParam, LPARAM _LParam),
		DllFunc(Input, void, SetKeyAction, DllArgs(Key _Key, std::function<void(Key)> _OnKeyDown, std::function<void(Key)> _OnKeyUp),
		DllFunc(Input, void, SetMouseBtnAction, DllArgs(MouseBtn _MouseBtn, std::function<void(MouseBtn, short2)> _OnMouseBtnDown, std::function<void(MouseBtn, short2)> _OnMouseBtnUp),
		DllFunc(Input, void, SetOnMouseMove, DllArgs(std::function<void(short2 _MousePos)> _OnMouseMove_),
		
		DllFunc(Input, bool, GetKeyState, DllArgs(Key _Key),
		
	EndDllFuncs(Input)
	))))))));
}