#include "pch.h"
#include "expat.h"
#include "XmlParseMaster.h"
#include "IXmlParseHelper.h"

#include <utility>
#include <fstream>

namespace SiachenGameEngine
{
	namespace Parsers
	{
		// TODO Test
		RTTI_DEFINITIONS(XmlParseMaster::SharedData)
			
		XmlParseMaster::XmlParseMaster(SharedData* sharedData) : mSharedData(sharedData), mIsClone(false)
		{
			// Initialize variables
			sharedData->SetXmlParseMaster(this);
			// Create an Expat object and register call backs
			mParser = XML_ParserCreate(NULL);
			XML_SetUserData(mParser, this);
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
		}

		XmlParseMaster::~XmlParseMaster()
		{
			XML_ParserFree(mParser);
		}

		XmlParseMaster* XmlParseMaster::Clone()
		{
			return nullptr;
		}

		void XmlParseMaster::AddHelper(const IXmlParseHelper& helper)
		{
			IXmlParseHelper* helperToAdd = const_cast<IXmlParseHelper*>(&helper);
			mHelperList.PushBack(helperToAdd);
		}

		bool XmlParseMaster::RemoveHelper(const IXmlParseHelper& helper)
		{
			IXmlParseHelper* helperToRemove = const_cast<IXmlParseHelper*>(&helper);
			return mHelperList.Remove(helperToRemove);
		}

		void XmlParseMaster::Parse(const char* buffer, std::uint32_t length, bool lastChunk)
		{
			std::int32_t done;
			if (lastChunk)
			{
				done = 1;
			}
			else
			{
				done = 0;
			}
			if (!XML_Parse(mParser, buffer, length, done))
			{
				throw std::runtime_error("Fatal error detected.");
			}
		}

		void XmlParseMaster::ParseFromFile(const std::string& fileName)
		{
			// TODO Parse or parse from file should be calling the initialize method on the shared data.
			mFileName = fileName;
			
			std::ifstream ifs(fileName);
			if (!ifs)
			{
				// TODO Check and confirm
				throw std::runtime_error("File doesn't exist.");
			}

			std::string content;
			content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
			// TODO Confirm
			std::uint32_t bufferLength = static_cast<std::uint32_t>(content.size()) + 1;
			
			Parse(content.c_str(), bufferLength, true);
		}

		const std::string & XmlParseMaster::GetFileName() const
		{
			return mFileName;
		}

		XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(const SharedData* sharedData)
		{
			mSharedData = const_cast<SharedData*>(sharedData);
		}

		void XmlParseMaster::StartElementHandler(void* userData, const char* element, const char** attribute)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			std::uint32_t helperCount = parser->mHelperList.Size();
			std::string elementString(element);

			Containers::HashMap<std::string, std::string> attributeHashmap;

			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				parser->GetAttributePairHashmap(attribute, attributeHashmap);
				if (parser->mHelperList.At(i)->StartElementHandler(elementString, attributeHashmap))
				{
					break;
				}
			}
		}

		void XmlParseMaster::EndElementHandler(void* userData, const char* element)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			std::uint32_t helperCount = parser->mHelperList.Size();
			std::string elementString(element);

			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				if (parser->mHelperList.At(i)->EndElementHandler(elementString))
				{
					break;
				}
			}
		}

		// TODO Implement
		void XmlParseMaster::CharDataHandler(void* userData, const char* str, std::int32_t length)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			parser;
			str;
			length;
			//std::uint32_t helperCount = parser->mHelperList.Size();

			//for (std::uint32_t i = 0; i < helperCount; ++i)
			//{
			//	parser->mHelperList.At(i)->CharDataHandler(str, length);
			//}
		}

		void XmlParseMaster::GetAttributePairHashmap(const char ** attributePairs, Containers::HashMap<std::string, std::string>& attributeMap)
		{
			attributeMap.Clear();

			std::string attributeName;
			std::string attributeValue;
			for (std::uint32_t i = 0; attributePairs[i]; i += 2)
			{
				attributeName = attributePairs[i];
				attributeValue = attributePairs[i + 1];
				attributeMap.Insert(std::make_pair(attributeName, attributeValue));
			}
		}

		XmlParseMaster::SharedData::SharedData() : mDepth(0), mParseMaster(nullptr)
		{

		}

		XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone()
		{
			return nullptr;
		}

		void XmlParseMaster::SharedData::SetXmlParseMaster(const XmlParseMaster* xmlParseMaster)
		{
			mParseMaster = const_cast<XmlParseMaster*>(xmlParseMaster);
		}

		XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
		{
			return mParseMaster;
		}

		void XmlParseMaster::SharedData::IncrementDepth()
		{
			++mDepth;
		}

		void XmlParseMaster::SharedData::DecrementDepth()
		{
			--mDepth;
		}

		std::uint32_t XmlParseMaster::SharedData::Depth() const
		{
			return mDepth;
		}

	}
}