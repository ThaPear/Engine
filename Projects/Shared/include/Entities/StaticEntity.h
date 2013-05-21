#pragma once

#define GetEntityStat(_Entity, _StatName)	(_Entity->m_EntityType->_StatName)

class Image;
class Path;
namespace Entities
{
	class EntityType;
	class StaticEntity
	{
	public:
		StaticEntity();

		int m_ImageFrame;

		float2 m_Pos;
		float m_Rotation;

		Entities::EntityType* m_EntityType;
	};
};