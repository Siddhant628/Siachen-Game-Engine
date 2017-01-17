#include "pch.h"
#include "CppUnitTest.h"
#include "_SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(_SListTest)
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

		TEST_METHOD(_SListPush)
		{
			SiachenGameEngine::_SList _list;
			
			int32_t data = 5;
			_list.PushFront(data);
			Assert::AreEqual(data, _list.Front());
			_list.PopFront();
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState _SListTest::sStartMemState;
}