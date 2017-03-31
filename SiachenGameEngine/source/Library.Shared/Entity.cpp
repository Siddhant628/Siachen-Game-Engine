#include "pch.h"
#include "Entity.h"
#include "Sector.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Entity)

		Entity::Entity()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void Entity::Populate()
		{
			AddExternalAttribute("name", &mEntityName, 1U);
		}

		const std::string& Entity::Name() const
		{
			return mEntityName;
		}

		void Entity::SetName(const std::string& entityName)
		{
			mEntityName = entityName;
		}

		Sector* Entity::GetSector() const
		{
			assert(GetParent()->Is(Sector::TypeIdClass()));
			return static_cast<Sector*>(GetParent());
		}

		void Entity::Update(WorldState& worldState)
		{
			worldState.mEntity = this;
			
			worldState.mEntity = nullptr;
		}
	}
}
