#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "SampleXmlParseHelper.h"
#include "SampleXmlSharedData.h"

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

		TEST_METHOD(First)
		{
			SampleXmlSharedData sharedData;
			XmlParseMaster parseMaster(&sharedData);

			SampleXmlParseHelper sampleHelper;
			sampleHelper.Initialize(&sharedData);

			parseMaster.AddHelper(sampleHelper);
			
			parseMaster.ParseFromFile("../../../XmlWithAttributes.xml");

			Assert::IsTrue(sharedData.GetStringPairVector().At(0).first == "Siddhant");
			Assert::IsTrue(sharedData.GetStringPairVector().At(0).second == "Grover");
			Assert::IsTrue(sharedData.GetStringPairVector().At(1).first == "Butter");
			Assert::IsTrue(sharedData.GetStringPairVector().At(1).second == "Chicken");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}