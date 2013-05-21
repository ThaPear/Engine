#include "Engine.h"
#include "DllAPIs\FileIO.h"
#include "DllAPIs\Window.h"
#include "DllAPIs\Renderer.h"
#include "DllAPIs\Input.h"
#include "DllAPIs\UI.h"
#include "DllAPIs\Game.h"

bool Engine::m_Active = false;
int Engine::m_TicksPerSecond = 20;

float Engine::m_TimePerTick = (1000 / (float)Engine::m_TicksPerSecond);


bool Engine::Init(int _NArgs, char *_Args[])
{
	PrintFuncEntry();
	MoveConsoleWindow(1680 + 808, 0, 660, 1050);

	if(!FileIO::Init())
	{
		return false;
	}

	// Set up the window.
	if(!Window::Init(Engine::HandleMessage))
	{
		return false;
	}
	if(!Renderer::Init(Window::GetHWND()))
	{
		return false;
	}
	if(!Input::Init())
	{
		return false;
	}
	if(!UI::Init())
	{

	}
	if(!Game::Init())
	{
		return false;
	}
	
	Window::ChangeStyle(WS_OVERLAPPEDWINDOW);
	Window::Move(1680, 0);
	Window::SetCaption("RTS v0.01");
	Window::Resize(800, 1000);

	// Set all key actions to simply go to the UI.
	for(int i = 0; i < Key::KeyMax; ++i)
		Input::SetKeyAction((Key)i,
							[](Key _Key){	UI::HandleKeyDown(_Key);	}, 
							[](Key _Key){	UI::HandleKeyUp(_Key);		});
	Input::SetKeyAction(Key::Plus,  [](Key _Key)
									{
										for(int c = 0; c < (Input::GetKeyState(Key::Alt)?100000:(Input::GetKeyState(Key::Ctrl)?10000:(Input::GetKeyState(Key::Shift)?5:1))); ++c)
											Engine::IncreaseTickRate();
										printf("TickRate = %i.\n", Engine::m_TicksPerSecond);
									},
									nullptr);
	Input::SetKeyAction(Key::Minus, [](Key _Key)
									{
										for(int c = 0; c < (Input::GetKeyState(Key::Alt)?100000:(Input::GetKeyState(Key::Ctrl)?10000:(Input::GetKeyState(Key::Shift)?5:1))); ++c)
											Engine::DecreaseTickRate();
										printf("TickRate = %i.\n", Engine::m_TicksPerSecond);
									},
									nullptr);
	for(int i = 0; i < MouseBtn::KeyMax; ++i)
		Input::SetMouseBtnAction(	(MouseBtn)i,
									[](MouseBtn _MouseBtn, short2 _MousePos){	UI::HandleMouseBtnDown(_MouseBtn, _MousePos);	},
									[](MouseBtn _MouseBtn, short2 _MousePos){	UI::HandleMouseBtnUp(_MouseBtn, _MousePos);		});

	Input::SetOnMouseMove(	[](short2 _MousePos){	UI::HandleMouseMove(_MousePos);	});

	Engine::m_Active = true;

	return true;
}

void Engine::Run()
{
	PrintFuncEntry();
	Timer timer;

	float passedTime = 0;
	float lastFrameTime = 0;
	
	while(Engine::m_Active)
	{
		lastFrameTime = max(0, timer.GetPassedTime());
		passedTime += lastFrameTime;
		timer.Start();
		Window::CatchMessages();
		while(passedTime > Engine::m_TimePerTick)
		{
			passedTime -= Engine::m_TimePerTick;
			Game::Tick();
		}

		Game::Render(passedTime / Engine::m_TimePerTick);
		UI::Render(lastFrameTime);
		Renderer::DisplayBuffer();
	}
}

void Engine::Terminate()
{
	PrintFuncEntry();

	Game::Terminate();
	UI::Terminate();
	Input::Terminate();
	Renderer::Terminate();
	Window::Terminate();
	FileIO::Terminate();
}

LRESULT CALLBACK Engine::HandleMessage( HWND _HWND, UINT _Message, WPARAM _WParam, LPARAM _LParam )
{
	switch(_Message)
	{
	case WM_MOVE:
		Window::Moved(	/* x */ _LParam & 0x0000ffff, /* y */ (_LParam & 0xffff0000) >> 16);		break;
	case WM_SIZE:
		Window::Resized( /* x */ _LParam & 0x0000ffff, /* y */ (_LParam & 0xffff0000) >> 16);
		Renderer::Resize(/* x */ _LParam & 0x0000ffff, /* y */ (_LParam & 0xffff0000) >> 16);
		g_ScreenSize = int2(_LParam & 0x0000ffff, (_LParam & 0xffff0000) >> 16);
		break;
	case WM_QUIT:
	case WM_CLOSE:
		printf("WM_QUIT or WM_CLOSE, quitting.\n");
		Engine::m_Active = false;
		break;
	default:
		if(!Input::HandleMessage(_HWND, _Message, _WParam, _LParam))
			return DefWindowProc(_HWND, _Message, _WParam, _LParam);
	}
	return 0;
}

void Engine::SetTickrate( int _TicksPerSecond )
{
	Engine::m_TicksPerSecond = max(1, _TicksPerSecond);
	Engine::m_TimePerTick = (1000 / (float)Engine::m_TicksPerSecond);
}

void Engine::IncreaseTickRate()
{
	Engine::SetTickrate(Engine::m_TicksPerSecond + 1);
}

void Engine::DecreaseTickRate()
{
	Engine::SetTickrate(Engine::m_TicksPerSecond - 1);
}