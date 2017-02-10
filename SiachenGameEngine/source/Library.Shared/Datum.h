#pragma once
#include "RTTI.h"
#include "glm/glm.hpp"

namespace SiachenGameEngine
{
	namespace Containers
	{
		enum class DatumType
		{
			Unknown,
			Integer,
			Float,
			Vector,
			Matrix,
			Table,
			String,
			Pointer
		};

		class Datum
		{
		private:
			union DatumValues
			{
				std::int32_t* i;
				float* f;
				glm::vec4* v;

			};
		};
	}
}