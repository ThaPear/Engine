#include "DllAPIs\Renderer.h"
#include "DllAPIs\Pathfinding.h"
#define DllExport
#pragma message("Game.cpp including DllAPIs/Game.h")
#include "DllAPIs\Game.h"

#include "Game.h"

#include "Entities\StaticEntity.h"
#include "Entities\EntityType.h"
#include "GameImpl.h"

#define LinearInterpolate(_P1, _P2, _X)	_P1 + (_P2 - _P1) * _X

namespace Game
{
	std::list<Entities::StaticEntity*> m_Entities;
	std::vector<Entities::EntityType*> m_EntityTypes;
};

void Game::LoadEntities()
{
	// TODO: Automatically detect entities.
}

///////////////////////////////////////////////////////////
//        ///  //////  /        ///  ///////  ///        //
//  //////  /  //////  /  //////  /  ///////  /  //////////
//        ///  //////  /        ///  ///////  /  //////////
//  /////////  //////  /  //////  /  ///////  /  //////////
//  ///////////      ///        ///        /  ///        //
///////////////////////////////////////////////////////////

bool Game::Init()
{
	PrintFuncEntry();
	if(!Pathfinding::Init())
		return false;
	
	Game::LoadEntities();
	if(!GameImpl::Init())
		return false;

	return true;
}

void Game::Terminate()
{
	PrintFuncEntry();

	GameImpl::Terminate();
}

void Game::Tick()
{
	//PrintFuncEntry();
	
	for(Entities::StaticEntity* staticEntity : Game::m_Entities)
	{
		
	}
	GameImpl::Tick();
}

void Game::Render(float _TickPercent)
{
	for(Entities::StaticEntity* staticEntity : Game::m_Entities)
	{
		Renderer::RenderImage(GetEntityStat(staticEntity, image), 0, staticEntity->m_Pos, GetEntityStat(staticEntity, size));
	}
	GameImpl::Render(_TickPercent);
}

////////////////////////////////////////////////////////////////
//      ///      ///  /  //////  ///    ///          /        //
//  ////  /  ////  /  /  //////  /  ////  /////  /////  ////////
//      ///      ///  ///  //  ///        /////  /////      ////
//  ///////  ///  //  ///  //  ///  ////  /////  /////  ////////
//  ///////  ////  /  /////  /////  ////  /////  /////        //
////////////////////////////////////////////////////////////////
