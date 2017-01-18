#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(SListTest)
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

		TEST_METHOD(SList_Constructors)
		{
			// Default constructor
			SiachenGameEngine::SList<int> list;
			Assert::AreEqual(list.IsEmpty(), true);

			auto expression = [&list] { list.Front(); };
			Assert::ExpectException<std::runtime_error>(expression);

			auto expression2 = [&list] { list.Back(); };
			Assert::ExpectException<std::runtime_error>(expression2);

			// Copy constructor
			list.PushBack(1);
			list.PushBack(2);
			list.PushBack(3);
			list.PushFront(0);

			SiachenGameEngine::SList<int> list2(list);

			Assert::AreEqual(list2.Front(), 0);
			Assert::AreEqual(list2.Back(), 3);
			Assert::AreEqual(list2.Size(), 4);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}