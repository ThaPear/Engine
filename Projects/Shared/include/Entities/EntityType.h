#pragma once

class Image;
namespace Entities
{
	class StaticEntity;

	class EntityType
	{
	public:
		EntityType(const char* _StaticEntityFolder);

		virtual StaticEntity* Create(float2 _Pos);

		typedef void (*pEnt_OnCreate)(StaticEntity* _Self);
		pEnt_OnCreate OnCreate;

		Image* image;
		int unitTypeID;
		float2 size;
	protected:
		EntityType();
	};
};