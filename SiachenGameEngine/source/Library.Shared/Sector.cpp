#include "pch.h"
#include "Sector.h"
#include "Datum.h"
#include "Factory.h"
#include "World.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Sector)

		Sector::Sector() : mEntityDatum(nullptr)
		{
			Populate();
			UpdatePrescribedAttributeInfo();
			mEntityDatum = Find("entities");
		}

		void Sector::Populate()
		{
			AddExternalAttribute("name", &mSectorName, 1U);
			AddInternalAttribute("entities", DatumType::TableType);
		}

		const std::string& Sector::Name() const
		{
			return mSectorName;
		}

		void Sector::SetName(const std::string& sectorName)
		{
			mSectorName = sectorName;
		}

		Datum& Sector::Entities()
		{
			return *mEntityDatum;
		}

		Entity* Sector::CreateEntity(const std::string& className, const std::string& instanceName)
		{
			Entity* entityCreated = Factory<Entity>::Create(className);

			if (entityCreated)
			{
				entityCreated->SetName(instanceName);
				AdoptEntity(*entityCreated);
			}
			return entityCreated;
		}

		World* Sector::GetWorld() const
		{
			assert(GetParent()->Is(World::TypeIdClass()));
			return static_cast<World*>(GetParent());
		}

		void Sector::AdoptEntity(Entity& entity)
		{
			Adopt(entity, "entities");
		}

		void Sector::Update(WorldState& worldState)
		{
			worldState.mSector = this;

			std::uint32_t size = mEntityDatum->Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				static_cast<Entity*>(mEntityDatum->Get<Scope*>(it))->Update(worldState);
			}

			worldState.mSector = nullptr;
		}
	}
}