#pragma once
#include "AbstractProductBar.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class ConcreteProductBar : public AbstractProductBar
		{
		public:
			virtual std::int32_t GetInteger() override;
		};

		ConcreteFactory(AbstractProductBar, ConcreteProductBar);
	}
}