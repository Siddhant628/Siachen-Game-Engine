#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Parsers;

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
			
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}