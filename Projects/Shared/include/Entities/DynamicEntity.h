#pragma once

#include "Entities\StaticEntity.h"

namespace Entities
{
	class EntityType;
	class DynamicEntity : public Entities::StaticEntity
	{
	public:
		DynamicEntity();

		float2 m_LastPos;
		float2 m_InterpolatedPos;

		float m_LastRotation;
		float m_InterpolatedRotation;
	};
};