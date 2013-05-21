#pragma once

#define DllByLib "Window.lib"
#	include "DllAPI.h"
#undef DllByLib

#ifndef DllExport
#	pragma comment(lib, "Window.lib")
#endif

namespace Window
{
	StartDllFuncs(
		DllFunc(Window, bool, Init, DllArgs(LRESULT (CALLBACK *_MessageHandler)(HWND _HWND, UINT _Message, WPARAM _WParam, LPARAM _LParam)),
		DllFunc(Window, void, Terminate, DllArgs(),

		DllFunc(Window, void, CatchMessages, DllArgs(),

		DllFunc(Window, void, Move, DllArgs(int _PosX, int _PosY),
		DllFunc(Window, void, Resize, DllArgs(int _SizeX, int _SizeY),
	
		DllFunc(Window, void, Resized, DllArgs(int _SizeX, int _SizeY),
		DllFunc(Window, void, Moved, DllArgs(int _PosX, int _PosY),
	
		DllFunc(Window, void, SetCaption, DllArgs(const char* _Caption),
		DllFunc(Window, void, ChangeStyle, DllArgs(int _Style),

		DllFunc(Window, HWND, GetHWND, DllArgs(),
	EndDllFuncs(Window
	))))))))))));
}