#define DllExport
#include "DllAPIs\Window.h"
#include "Window.h"


bool Window::Init(LRESULT (CALLBACK *_MessageHandler)(HWND, UINT, WPARAM, LPARAM))
{
	PrintFuncEntry();

	// Create and register the wndClass.
	{
		WNDCLASS wndClass = 
		{
			CS_HREDRAW | CS_VREDRAW | CS_OWNDC,	// style,			Style.
			_MessageHandler,					// lpfnWndProc,		Message handler routine.
			0,									// cbClsExtra
			0,									// cbWndExtra
			NULL,								// hInstance
			LoadIcon(NULL, IDI_APPLICATION),	// hIcon,			Icon.
			LoadCursor(NULL, IDC_ARROW),		// hCursor,			Cursor.
			NULL,//(HBRUSH)GetStockObject(WHITE_BRUSH),// hbrBackground,	Background color.
			NULL,								// lpszMenuName
			TEXT("Window")						// lpszClassName,	Class Name to register this WNDCLASS under.
		};

		RegisterClass(&wndClass);
	}

	// Adjust window size to accommodate the title bar.
	RECT trueWindowRect = {0, 0, Window::m_SizeX, Window::m_SizeY	};
	AdjustWindowRect(&trueWindowRect, Window::m_Style, FALSE);

	// Create the HWND.
	Window::m_HWND = CreateWindow(	TEXT("Window"),								// window class name
									TEXT(""),									// window caption
									0,											// window style
									0,											// initial x position
									0,											// initial y position
									trueWindowRect.right - trueWindowRect.left,	// initial x size
									trueWindowRect.bottom - trueWindowRect.top,	// initial y size
									NULL,										// parent window handle
									NULL,										// window menu handle
									NULL,										// program instance handle
									NULL);										// creation parameters

	if(Window::m_HWND == NULL)
	{
		int err = GetLastError();
		printf("Window::Init HWND creation failed, Error 0x%x, %i.\n", err, err);
	
		return false;
	}

	ShowWindow(Window::m_HWND, SW_SHOW);

	return true;
}

void Window::Terminate()
{
	PrintFuncEntry();
}

void Window::CatchMessages()
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::Move(int _PosX, int _PosY)
{
	Window::m_PosX = _PosX;
	Window::m_PosY = _PosY;
	RECT curWindowRect;
	GetWindowRect(Window::m_HWND, &curWindowRect);
	
	SetWindowPos(	Window::m_HWND,
					NULL,
					Window::m_PosX,
					Window::m_PosY,
					curWindowRect.right - curWindowRect.left,
					curWindowRect.bottom - curWindowRect.top,
					0
				);
}

void Window::Resize(int _SizeX, int _SizeY)
{
	printf("Window::Resize(%i, %i).\n", _SizeX, _SizeY);
	Window::m_SizeX = _SizeX;
	Window::m_SizeY = _SizeY;
	RECT curWindowRect;
	GetWindowRect(m_HWND, &curWindowRect);
	
	RECT trueWindowRect = {0, 0, Window::m_SizeX, Window::m_SizeY	};
	AdjustWindowRect(&trueWindowRect, Window::m_Style, FALSE);

	SetWindowPos(	Window::m_HWND,
					NULL,
					curWindowRect.left,
					curWindowRect.top,
					trueWindowRect.right - trueWindowRect.left,
					trueWindowRect.bottom - trueWindowRect.top,
					0
				);
}

void Window::Moved(int _PosX, int _PosY)
{
	Window::m_PosX = _PosX;
	Window::m_PosY = _PosY;
}

void Window::Resized(int _SizeX, int _SizeY)
{
	Window::m_SizeX = _SizeX;
	Window::m_SizeY = _SizeY;
}

void Window::SetCaption(const char* _Caption)
{
	SetWindowText(Window::m_HWND, _Caption);
}

void Window::ChangeStyle(int _Style)
{
	Window::m_Style = _Style;

	SetWindowLong(Window::m_HWND, GWL_STYLE, Window::m_Style);
	ShowWindow(Window::m_HWND, SW_SHOW);

	// Resize, since the title bar and borders may have changed.
	Resize(Window::m_SizeX, Window::m_SizeY);
}

HWND Window::GetHWND()
{
	return Window::m_HWND;
}