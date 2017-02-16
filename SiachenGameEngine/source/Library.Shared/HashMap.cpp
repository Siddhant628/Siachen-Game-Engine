#include "HashMap.h"

namespace SiachenGameEngine
{
	namespace Containers
	{
		std::uint32_t DefaultHash<char*>::operator()(char* key) const
		{
			std::uint32_t numberOfBytes = static_cast<std::uint32_t>(strlen(key));
			std::uint32_t hashValue = 0;

			for (std::uint32_t i = 0; i < numberOfBytes; ++i)
			{
				hashValue = hashValue + key[i];
			}
			return hashValue;
		}
		
		std::uint32_t DefaultHash<std::string>::operator()(const std::string &key) const
		{
			const char* str = key.c_str();
			std::uint32_t numberOfBytes = static_cast<std::uint32_t>(strlen(str));
			std::uint32_t hashValue = 0;

			for (std::uint32_t i = 0; i < numberOfBytes; ++i)
			{
				hashValue = hashValue + key[i];
			}
			return hashValue;
		}

		// Comparison Functions

		bool DefaultCompareFunctor<char*>::operator()(char* first, char* second)
		{
			std::int32_t comparisonResult = strcmp(first, second);

			if (comparisonResult == 0)
			{
				return true;
			}
			return false;
		}

	}
}