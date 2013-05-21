#pragma once

#define DllByLib "Pathfinding.lib"
#	include "DllAPI.h"
#undef DllByLib

class Path;
namespace Pathfinding
{
	StartDllFuncs(
		DllFunc(Pathfinding, bool, Init, DllArgs(),
		DllFunc(Pathfinding, void, Terminate, DllArgs(),

		DllFunc(Pathfinding, Path*, GetPath, DllArgs(float2 _From, float2 _To),
	EndDllFuncs(Pathfinding)
	))));
}