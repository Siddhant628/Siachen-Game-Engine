#include "pch.h"
#include "CppUnitTest.h"

#include "Attributed.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedTest)
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

		TEST_METHOD(Attributed_First)
		{
			AttributedFoo foo;
			AttributedBar bar;
			Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attributed_Second)
		{
			AttributedFoo foo;
			AttributedFoo foo2;
			AttributedBar bar;
			AttributedBar bar2;
			Attributed::ClearCacheHashmap();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}