#pragma once
#include "IXmlParseHelper.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class SampleXmlParseHelper : public Parsers::IXmlParseHelper
		{
		public:
			/**
			* Initializes this helper.
			*/
			virtual void Initialize() override;
			/**
			* Attempts to handle the element start.
			* @param elementName The name of the element.
			* @param attributeHashmap A hashmap containing attribute name-value pairs.
			* @return True if the handler does handle this element.
			*/
			virtual bool StartElementHandler(const char* elementName, Containers::HashMap<std::string, std::string> attributeHashmap) override;
			/**
			* Attempts to handle the element end.
			* @param elementName The name of the element.
			* @return True if the handler does handle this element.
			*/
			virtual bool EndElementHandler(const char* elementName) override;
			/**
			* Given a string buffer of character data, attempt to handle the data.
			* @param characterData The buffer of data which has to be handled.
			* @param size The number of bytes in the character data buffer.
			* @return True if the handler does handle the character data.
			*/
			virtual bool CharDataHandler(const char* characterData, std::int32_t size) override;
			/**
			* Makes a duplicate of this helper.
			* @return A pointer to a duplicate of this helper.
			*/
			virtual IXmlParseHelper* Clone() override;
		};
	}
}
