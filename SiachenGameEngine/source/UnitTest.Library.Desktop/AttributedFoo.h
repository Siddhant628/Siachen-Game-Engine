#pragma once
#include "Attributed.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class AttributedFoo : public GameplayFramework::Attributed
		{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)

		private:
			std::int32_t mInteger;
		
		public:
			AttributedFoo();
			virtual ~AttributedFoo() = default;
			void Populate() override;

			std::int32_t GetInteger();

			void SetInteger(std::int32_t);

		};
	}
}