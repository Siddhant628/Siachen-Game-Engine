#pragma once
#include <string>
#include "HashMap.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		/**
		* An abstract base class for producing concrete handlers for parsing specific elements.
		*/
		class IXmlParseHelper
		{
		public:
			/**
			* Default constructor for the abstract base class.
			*/
			IXmlParseHelper() = default;
			/**
			* Destructor for the abstract base class.
			*/
			virtual ~IXmlParseHelper() =default;
			/**
			* Initializes this helper.
			*/
			virtual void Initialize(XmlParseMaster::SharedData& sharedData) = 0;
			/**
			* Attempts to handle the element start.
			* @param elementName The name of the element.
			* @param attributeHashmap A hashmap containing attribute name-value pairs.
			* @return True if the handler does handle this element.
			*/
			virtual bool StartElementHandler(const std::string& elementName, Containers::HashMap<std::string, std::string> attributeHashmap) = 0;
			/**
			* Attempts to handle the element end.
			* @param elementName The name of the element.
			* @return True if the handler does handle this element.
			*/
			virtual bool EndElementHandler(const std::string& elementName) = 0;
			/**
			* Given a string buffer of character data, attempt to handle the data.
			* @param characterData The buffer of data which has to be handled.
			* @param size The number of bytes in the character data buffer.
			*/
			virtual void CharDataHandler(const char* characterData, std::uint32_t size) = 0;
			/**
			* Makes a duplicate of this helper.
			* @return A pointer to a duplicate of this helper.
			*/
			virtual IXmlParseHelper* Clone() = 0;
		};
	}
}