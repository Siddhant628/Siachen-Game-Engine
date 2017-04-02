#pragma once
#include "Entity.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class EntityFoo : public GameplayFramework::Entity
		{
		RTTI_DECLARATIONS(EntityFoo, Entity)
		public:
			std::int32_t mInt;
			std::float_t mFloat;
			std::string mString;
			glm::vec4 mVector;
		public:
			EntityFoo();
			~EntityFoo() = default;
			virtual void Populate() override;
		};

		ConcreteFactory(GameplayFramework::Entity, EntityFoo)
	}
}