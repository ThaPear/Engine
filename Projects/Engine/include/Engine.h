#pragma once

class Engine
{
public:
	static bool Init(int _NArgs, char *_Args[]);
	static void Run();
	static void Terminate();

	static LRESULT CALLBACK HandleMessage(HWND _HWND, UINT _Message, WPARAM _WParam, LPARAM _LParam);

	static void SetTickrate(int _TicksPerSecond);
	static void IncreaseTickRate();
	static void DecreaseTickRate();

	static bool m_Active;

	static int m_TicksPerSecond;
	static float m_TimePerTick;
};