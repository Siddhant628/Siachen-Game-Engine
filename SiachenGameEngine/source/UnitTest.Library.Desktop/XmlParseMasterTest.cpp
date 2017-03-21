#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "SampleXmlParseHelper.h"
#include "SampleXmlSharedData.h"
#include "AnotherSharedData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlParseMasterTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(XmlParseMaster_ParseFileWithAttributes)
		{
			SampleXmlSharedData sharedData;
			XmlParseMaster parseMaster(sharedData);

			SampleXmlParseHelper sampleHelper;
			parseMaster.AddHelper(sampleHelper);
			
			parseMaster.ParseFromFile("../../../XmlWithAttributes.xml");

			Assert::IsTrue(sharedData.GetStringPairVector().At(0).first == "Siddhant");
			Assert::IsTrue(sharedData.GetStringPairVector().At(0).second == "Grover");
			Assert::IsTrue(sharedData.GetStringPairVector().At(1).first == "Butter");
			Assert::IsTrue(sharedData.GetStringPairVector().At(1).second == "Chicken");
		}

		TEST_METHOD(XmlParseMaster_ParseFileWithoutAttributes)
		{
			SampleXmlSharedData sharedData;
			XmlParseMaster parseMaster(sharedData);

			SampleXmlParseHelper sampleHelper;
			parseMaster.AddHelper(sampleHelper);

			parseMaster.ParseFromFile("../../../XmlWithoutAttributes.xml");

			Assert::IsTrue(sharedData.GetStringPairVector().At(0).first == "Siddhant");
			Assert::IsTrue(sharedData.GetStringPairVector().At(0).second == "Grover");
			Assert::IsTrue(sharedData.GetStringPairVector().At(1).first == "Butter");
			Assert::IsTrue(sharedData.GetStringPairVector().At(1).second == "Chicken");
		}

		TEST_METHOD(XmlParseMaster_GettersAndSetters)
		{
			SampleXmlSharedData sharedData;
			XmlParseMaster parseMaster(sharedData);

			SampleXmlParseHelper sampleHelper;
			parseMaster.AddHelper(sampleHelper);

			parseMaster.ParseFromFile("../../../XmlWithAttributes.xml");

			// Get file name
			Assert::IsTrue(parseMaster.GetFileName() == "../../../XmlWithAttributes.xml");
			
			// Get shared data
			Assert::IsTrue(parseMaster.GetSharedData() == &sharedData);

			// Set shared data
			SampleXmlSharedData anotherSharedData;
			parseMaster.SetSharedData(anotherSharedData);
			Assert::IsTrue(parseMaster.GetSharedData() == &anotherSharedData);
		}

		TEST_METHOD(XmlParseMaster_Methods)
		{
			// Parse from file which isn't found
			SampleXmlSharedData sharedData;
			XmlParseMaster parseMaster(sharedData);

			SampleXmlParseHelper sampleHelper;
			parseMaster.AddHelper(sampleHelper);

			auto fileExpression = [&parseMaster] {parseMaster.ParseFromFile("NoFile.xml"); };
			Assert::ExpectException<std::exception>(fileExpression);

			// Adding and removing helpers

			SampleXmlParseHelper sampleHelper2;
			parseMaster.AddHelper(sampleHelper2);
			parseMaster.RemoveHelper(sampleHelper);

			parseMaster.ParseFromFile("../../../XmlWithAttributes.xml");
		}

		TEST_METHOD(XmlParseMaster_IXmlParseHelper)
		{
			// Initialize of parse helper
			AnotherSharedData sharedData;
			SampleXmlParseHelper parseHelper;

			auto constructorExpression = [&parseHelper, &sharedData] { parseHelper.Initialize(sharedData); };
			Assert::ExpectException<std::exception>(constructorExpression);

		}

		TEST_METHOD(XmlParseMaster_XmlSharedData)
		{
			SampleXmlSharedData sharedData;
			XmlParseMaster parseMaster(sharedData);

			SampleXmlParseHelper sampleHelper;
			parseMaster.AddHelper(sampleHelper);

			parseMaster.ParseFromFile("../../../XmlWithAttributes.xml");

			// Get parse master
			Assert::IsTrue(sharedData.GetXmlParseMaster() == &parseMaster);

			// Initialize shared data
			Assert::AreEqual(sharedData.GetStringPairVector().Size(), 2U);
			Assert::IsTrue(sharedData.GetCurrentElement() == "Student");
			sharedData.Initialize();
			Assert::AreEqual(sharedData.GetStringPairVector().Size(), 0U);
			Assert::IsTrue(sharedData.GetCurrentElement() == "");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}