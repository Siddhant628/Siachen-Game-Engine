#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "XmlSharedDataTable.h"

#include "Scope.h"

#include "XmlParseHelperTable.h"
#include "XmlParseHelperPrimitives.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::Containers;

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

		TEST_METHOD(XmlTableParserTest_Primitives)
		{
			XmlSharedDataTable sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperTable tableHelper;
			XmlParseHelperPrimitives primitiveHelper;
			parseMaster.AddHelper(tableHelper);
			parseMaster.AddHelper(primitiveHelper);

			parseMaster.ParseFromFile("../../../XmlWithTable.xml");

			std::int32_t int1 = (*sharedData.mScope)["Child1"][0]["Int1"].Get<std::int32_t>();
			Assert::AreEqual(int1, 10);
			std::int32_t intArray1 = (*sharedData.mScope)["Child2"][0]["IntArray"].Get<std::int32_t>();
			Assert::AreEqual(intArray1, 20);
			std::int32_t intArray2 = (*sharedData.mScope)["Child2"][0]["IntArray"].Get<std::int32_t>(1);
			Assert::AreEqual(intArray2, 30);
			std::int32_t int2 = (*sharedData.mScope)["Child2"][1]["Int2"].Get<std::int32_t>();
			Assert::AreEqual(int2, 40);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlTableParserTest::sStartMemState;
}