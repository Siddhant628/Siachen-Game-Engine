#pragma once
#include <string>

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
			* Initializes this helper.
			*/
			virtual void Initialize() = 0;
			/**
			* Attempts to handle the element start.
			* @param elementName The name of the element.
			* @param attributePairs An array of attribute name-value pairs.
			* @return True if the handler does handle this element.
			*/
			virtual bool StartElementHandler(const char* elementName, const char** attributePairs) = 0;
			/**
			* Attempts to handle the element end.
			* @param elementName The name of the element.
			* @return True if the handler does handle this element.
			*/
			virtual bool EndElementHandler(const char* elementName) = 0;
			/**
			* Given a string buffer of character data, attempt to handle the data.
			* @param characterData The buffer of data which has to be handled.
			* @param size The number of bytes in the character data buffer.
			* @return True if the handler does handle the character data.
			*/
			virtual bool CharDataHandler(const char* characterData, std::int32_t size) = 0;
			/**
			* Makes a duplicate of this helper.
			* @return A pointer to a duplicate of this helper.
			*/
			virtual IXmlParseHelper* Clone() = 0;

			// TODO Understand Hint: What qualifier should the destructor have?
		};
	}
}