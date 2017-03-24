#include "pch.h"
#include "expat.h"
#include "XmlParseMaster.h"
#include "IXmlParseHelper.h"
#include "Vector.h"

#include <utility>
#include <fstream>

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(XmlParseMaster::SharedData)

		XmlParseMaster::XmlParseMaster(SharedData& sharedData) : mParser(XML_ParserCreate(NULL)) , mSharedData(&sharedData), mIsClone(false), mCurrentHelper(nullptr)
		{
			sharedData.SetXmlParseMaster(*this);
		}

		XmlParseMaster::~XmlParseMaster()
		{
			XML_ParserFree(mParser);

			if (mIsClone)
			{

				std::uint32_t size = mHelperList.Size();
				for (std::uint32_t i = 0; i < size; ++i)
				{
					delete mHelperList.At(i);
				}

				delete mSharedData;
			}
		}

		XmlParseMaster* XmlParseMaster::Clone()
		{
			SharedData* sharedDataClone = mSharedData->Clone();
			XmlParseMaster* parseMasterClone = new XmlParseMaster(*sharedDataClone);

			std::uint32_t size = mHelperList.Size();
			for (std::uint32_t i = 0; i < size; ++i)
			{
				IXmlParseHelper* helperClone = mHelperList.At(i)->Clone();
				parseMasterClone->AddHelper(*helperClone);
			}

			parseMasterClone->mFileName = mFileName;
			parseMasterClone->mIsClone = true;
			return parseMasterClone;
		}

		void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
		{
			// Disallow adding of helpers to cloned master parsers
			if (mIsClone)
			{
				throw std::runtime_error("Cannot add helpers to a cloned parser.");
			}
			if (mHelperList.Find(&helper) != mHelperList.end())
			{
				throw std::runtime_error("Cannot add the same helper twice.");
			}
			mHelperList.PushBack(&helper);
		}

		bool XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
		{
			if (mIsClone)
			{
				throw std::runtime_error("Cannot remove helpers from a cloned parser.");
			}
			return mHelperList.Remove(&helper);
		}

		void XmlParseMaster::Parse(const char* buffer, std::uint32_t length, bool lastChunk)
		{
			ResetParseMaster();
			// Check for last chunk
			std::int32_t done;
			if (lastChunk)
			{
				done = 1;
			}
			else
			{
				done = 0;
			}
			// Actual parsing of the file
			if (!XML_Parse(mParser, buffer, length, done))
			{
				throw std::runtime_error("Fatal error detected.");
			}
		}

		void XmlParseMaster::ParseFromFile(const std::string& fileName)
		{
			mFileName = fileName;

			std::ifstream ifs(fileName);
			if (!ifs)
			{
				throw std::runtime_error("File doesn't exist.");
			}
			std::string content;
			content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
			Parse(content.c_str(), static_cast<std::uint32_t>(content.size()), true);
			ifs.close();
		}

		const std::string& XmlParseMaster::GetFileName() const
		{
			return mFileName;
		}

		XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(SharedData& sharedData)
		{
			// TODO Ask Paul that allowing deletion seems ugly as now user will have to heap allocate the other shared data.
			if (mIsClone)
			{
				throw std::runtime_error("Cannot update the shared data of the clone.");
			}
			mSharedData = &sharedData;
		}

		void XmlParseMaster::StartElementHandler(void* userData, const char* element, const char** attribute)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			std::uint32_t helperCount = parser->mHelperList.Size();
			std::string elementString(element);

			Containers::HashMap<std::string, std::string> attributeHashmap;

			parser->GetSharedData()->IncrementDepth();

			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				parser->GetAttributePairHashmap(attribute, attributeHashmap);
				if (parser->mHelperList.At(i)->StartElementHandler(elementString, attributeHashmap))
				{
					parser->mCurrentHelper = parser->mHelperList.At(i);
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
					parser->mCurrentHelper = nullptr;
					break;
				}
			}
			// TODO Confirm if depth decrement should be happening after
			parser->GetSharedData()->DecrementDepth();
		}

		void XmlParseMaster::CharDataHandler(void* userData, const char* str, std::int32_t length)
		{
			XmlParseMaster* parser = reinterpret_cast<XmlParseMaster*>(userData);
			if (parser->mCurrentHelper)
			{
				parser->mCurrentHelper->CharDataHandler(str, length);
			}
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

		void XmlParseMaster::ResetParseMaster()
		{
			// Reset the parser
			XML_ParserReset(mParser, nullptr);
			XML_SetUserData(mParser, this);
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
			// Initialize all the helpers and shared data
			mSharedData->Initialize();
			mSharedData->SetXmlParseMaster(*this);
			std::uint32_t helperCount = mHelperList.Size();
			for (std::uint32_t i = 0; i < helperCount; ++i)
			{
				mHelperList.At(i)->Initialize(*mSharedData);
			}
		}

		XmlParseMaster::SharedData::SharedData() : mDepth(0), mParseMaster(nullptr)
		{

		}

		void XmlParseMaster::SharedData::Initialize()
		{
			mParseMaster = nullptr;
			mDepth = 0;
		}

		void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster& xmlParseMaster)
		{
			mParseMaster = &xmlParseMaster;
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
			if (mDepth > 0)
			{
				--mDepth;
			}
		}

		std::uint32_t XmlParseMaster::SharedData::Depth() const
		{
			return mDepth;
		}

	}
}