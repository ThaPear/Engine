#include <windows.h>
#include <stdio.h>

#pragma warning(disable:4996)

__forceinline void OpenConsoleWindow()
{
	// Open console window & redirect std io
	AllocConsole();
	freopen("CONIN$","rb",stdin);
	freopen("CONOUT$","wb",stdout);
	freopen("CONOUT$","wb",stderr);

	atexit((void(*)())FreeConsole);
}

__forceinline void MoveConsoleWindow(int _X, int _Y, int _W, int _H)
{
	MoveWindow(GetConsoleWindow(), _X, _Y, _W, _H, TRUE);
}

#pragma warning(default:4996)