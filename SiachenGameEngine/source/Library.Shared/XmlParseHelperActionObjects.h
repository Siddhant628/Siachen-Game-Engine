#pragma once
#include "IXmlParseHelper.h"
#include "XmlSharedDataWorld.h"
#include "Action.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		/**
		* A XML parsing helper which can parse ActionCreateAction and ActionDestroyAction. It can handle instantiation and destruction of action objects.
		*/
		class XmlParseHelperActionObjects final : public IXmlParseHelper
		{
		public:
			/**
			* Default constructor initializes values.
			*/
			XmlParseHelperActionObjects();
			/**
			* Destructor.
			*/
			~XmlParseHelperActionObjects() = default;
			/**
			* Initializes this helper.
			*/
			virtual void Initialize(XmlParseMaster::SharedData& sharedData) override;
			/**
			* Attempts to handle the element start.
			* @param elementName The name of the element.
			* @param attributeHashmap A hashmap containing attribute name-value pairs.
			* @return True if the handler does handle this element.
			*/
			virtual bool StartElementHandler(const std::string& elementName, const Containers::HashMap<std::string, std::string>& attributeHashmap) override;
			/**
			* Attempts to handle the element end.
			* @param elementName The name of the element.
			* @return True if the handler does handle this element.
			*/
			virtual bool EndElementHandler(const std::string& elementName) override;
			/**
			* Given a string buffer of character data, attempt to handle the data.
			* @param characterData The buffer of data which has to be handled.
			* @param size The number of bytes in the character data buffer.
			*/
			virtual void CharDataHandler(const char* characterData, std::uint32_t size) override;
			/**
			* Makes a duplicate of this helper.
			* @return A pointer to a duplicate of this helper.
			*/
			virtual IXmlParseHelper* Clone() override;
		private:
			GameplayFramework::Action* GetActionObject(const std::string& className, const std::string& instanceName);
			/**
			* A pointer to the shared data.
			*/
			XmlSharedDataWorld* mSharedData;

		};
	}
}