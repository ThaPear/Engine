#pragma once

namespace Window
{
	HWND m_HWND;
	int m_SizeX = 320, m_SizeY = 240;
	int m_PosX = 0, m_PosY = 0;
	int m_Style = WS_SYSMENU | WS_CAPTION; // Default style.
};