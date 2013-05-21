#define DllExport
#include "DllAPIs\Pathfinding.h"
#include "Pathfinding.h"
#include "Path.h"

bool Pathfinding::Init()
{
	PrintFuncEntry();

	return true;
}

void Pathfinding::Terminate()
{
	PrintFuncEntry();
}

Path* Pathfinding::GetPath(float2 _From, float2 _To)
{
	Path* path = new Path();

	path->m_Positions.push_back(_To);

	return path;
}