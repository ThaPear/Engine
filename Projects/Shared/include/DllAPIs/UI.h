#pragma once

#define DllByLib "UI.lib"
#	include "DllAPI.h"
#undef DllByLib

namespace UI
{
	StartDllFuncs(
		DllFunc(UI, bool, Init, DllArgs(),
		DllFunc(UI, void, Terminate, DllArgs(),

		DllFunc(UI, void, Render, DllArgs(float _LastFrameTime),

		DllFunc(UI, void, HandleKeyDown, DllArgs(Key _Key),
		DllFunc(UI, void, HandleKeyUp, DllArgs(Key _Key),

		DllFunc(UI, void, HandleMouseBtnDown, DllArgs(MouseBtn _MouseBtn, short2 _MousePos),
		DllFunc(UI, void, HandleMouseBtnUp, DllArgs(MouseBtn _MouseBtn, short2 _MousePos),
		
		DllFunc(UI, void, HandleMouseMove, DllArgs(short2 _MousePos),
	EndDllFuncs(UI)
	)))))))));
}