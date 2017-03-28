#pragma once
#include <cstdint>

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class AbstractProductBar
		{
		public:
			virtual std::int32_t GetInteger() = 0;
		};
	}
}