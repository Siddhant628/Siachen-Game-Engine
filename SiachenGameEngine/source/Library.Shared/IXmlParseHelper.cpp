#include "IXmlParseHelper.h"
#include "HashMap.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		void IXmlParseHelper::ValidateAttributeHashmap(const Containers::HashMap<std::string, std::string>& attributeHashmap) const
		{
			HashMap<std::string, std::string>::Iterator it = attributeHashmap.Find("Name");
			if (it == attributeHashmap.end())
			{
				throw std::runtime_error("All elements must have a name");
			}
		}
	}
}