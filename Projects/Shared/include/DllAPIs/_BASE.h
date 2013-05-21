#pragma once

#define DllByLib "_BASE.lib"
#	include "DllAPI.h"
#undef DllByLib

namespace _BASE
{
	StartDllFuncs(
		DllFunc(_BASE, bool, Init, DllArgs(),
		DllFunc(_BASE, void, Terminate, DllArgs(),

	EndDllFuncs(_BASE)
	)));
}