#include "pch.h"
#include "XmlParseMaster.h"
#include "expat.h"

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
			XML_Parser parser = XML_ParserCreate(nullptr);
			XML_SetUserData(parser, this);
			XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(parser, CharElementHandler);
		}

		XmlParseMaster::~XmlParseMaster()
		{

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

		void XmlParseMaster::ParseFromFile(const std::string& fileName)
		{
			mFileName = fileName;
			
			std::ifstream ifs(fileName);
			if (!ifs)
			{
				// TODO Check and confirm
				throw std::runtime_error("File doesn't exist.");
			}

			std::string content;
			content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

			std::uint32_t bufferLength = content.size() + 1;
			
			Parse(content.c_str(), bufferLength);
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

			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				if (parser->mHelperList.At(i)->StartElementHandler(element, attribute))
				{
					break;
				}
			}
		}

		void XmlParseMaster::EndElementHandler(void* userData, const char* element)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			std::uint32_t helperCount = parser->mHelperList.Size();

			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				if (parser->mHelperList.At(i)->EndElementHandler(element))
				{
					break;
				}
			}
		}

		void XmlParseMaster::CharElementHandler(void* userData, const char* str, std::int32_t length)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			std::uint32_t helperCount = parser->mHelperList.Size();

			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				if (parser->mHelperList.At(i)->CharDataHandler(str, length))
				{
					break;
				}
			}
		}

		XmlParseMaster::SharedData::SharedData() : mDepth(0), mParseMaster(nullptr)
		{

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