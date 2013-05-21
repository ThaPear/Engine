#pragma once

#define DllByLib "Game.lib"
#	include "DllAPI.h"
#undef DllByLib

#ifndef DllExport
#	pragma comment(lib, "Game.lib")
#endif


class Order;
namespace Entities
{
	class Unit;
	class UnitType;
	class ConstructionSite;
}
namespace Game
{
	StartDllFuncs(
		DllFunc(Game, bool, Init, DllArgs(),
		DllFunc(Game, void, Terminate, DllArgs(),

		DllFunc(Game, void, Tick, DllArgs(),
		DllFunc(Game, void, Render, DllArgs(float _TickPercent),

		DllFunc(Game, std::list<Entities::Unit*>, GetUnitsInArea, DllArgs(float2 _Pos1, float2 _Pos2),
		DllFunc(Game, std::list<Entities::Unit*>, GetUnitsInRadius, DllArgs(float2 _Pos, float _Radius),
		DllFunc(Game, std::list<Entities::Unit*>, GetUnitsAtPoint, DllArgs(float2 _Pos),

		DllFunc(Game, void, IssueMoveOrder, DllArgs(std::list<Entities::Unit*> _Units, bool _Queue, float2 _Pos),
		DllFunc(Game, void, IssueConstructionOrder, DllArgs(std::list<Entities::Unit*> _Units, bool _Queue, float2 _Pos, Entities::UnitType* _TargetUnitType),

		DllFunc(Game, void, SetOnOrdersChanged, DllArgs(std::function<void(std::list<Order*>*)> _OnOrdersChanged),
		
		DllFunc(Game, Entities::ConstructionSite*, StartBuildingConstruction, DllArgs(float2 _TargetLocation, Entities::UnitType* _UnitType),
		DllFunc(Game, void, FinishBuildingConstruction, DllArgs(Entities::ConstructionSite* _ConstructionSite),

		DllFunc(Game, Entities::UnitType*, GetUnitTypeByID, DllArgs(int _ID),

		DllFunc(Game, void, CreateUnit, DllArgs(float2 _TargetLocation, Entities::UnitType* _UnitType),
	EndDllFuncs(Game)
	)))))))))))))));
}