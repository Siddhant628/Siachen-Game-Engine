#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "XmlSharedDataTable.h"

#include "XmlParseHelperTable.h"
#include "XmlParseHelperInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Parsers;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlTableParserTest)
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

		TEST_METHOD(XmlTableParserTest_BaseScope)
		{
			XmlSharedDataTable sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperTable tableHelper;
			parseMaster.AddHelper(tableHelper);

			parseMaster.ParseFromFile("../../../XmlWithTable.xml");

			Assert::AreEqual(sharedData.Depth(), 0U);

			//XmlParseHelperInteger integerHelper;
			//parseMaster.AddHelper(integerHelper);

			parseMaster.ParseFromFile("../../../XmlWithTable.xml");
			
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlTableParserTest::sStartMemState;
}