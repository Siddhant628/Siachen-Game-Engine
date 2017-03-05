#pragma once
#include "AttributedFoo.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class AttributedBar : public AttributedFoo
		{
			RTTI_DECLARATIONS(AttributedBar, AttributedFoo)

		private:
			std::float_t mFloat;

		public:
			AttributedBar();
			void Populate() override;

		};
	}
}