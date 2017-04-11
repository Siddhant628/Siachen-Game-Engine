#include "pch.h"
#include "CppUnitTest.h"
#include "Event.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Events;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTest)
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

		TEST_METHOD(EventFirst)
		{
			std::int32_t integer;
			Event<std::int32_t> event(integer, false);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
};