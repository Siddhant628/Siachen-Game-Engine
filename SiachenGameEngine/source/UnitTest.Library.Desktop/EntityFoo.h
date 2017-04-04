#pragma once
#include "Entity.h"
#include "Factory.h"
#include "WorldState.h"

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
			glm::mat4x4 mMatrix;
		protected:
			virtual void Populate() override;
		public:
			EntityFoo();
			~EntityFoo() = default;
			// TODO Can be changed to parents method
			virtual void Update(GameplayFramework::WorldState& worldState) override;
		};

		ConcreteFactory(GameplayFramework::Entity, EntityFoo)
	}
}