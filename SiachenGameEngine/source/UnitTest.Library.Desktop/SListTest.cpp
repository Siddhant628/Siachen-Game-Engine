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
			SiachenGameEngine::SList<int32_t> list;
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

		TEST_METHOD(SList_PushFront)
		{
			SiachenGameEngine::SList<int32_t*> list;

			// Pushing the first item
			int32_t data = 5;
			list.PushFront(&data);
			Assert::AreEqual(&data, list.Front());
			Assert::AreEqual(&data, list.Back());

			// Pushing more items
			int32_t data2 = 10;
			list.PushFront(&data2);
			Assert::AreEqual(&data2, list.Front());

			int32_t data3 = 15;
			list.PushFront(&data3);
			Assert::AreEqual(&data3, list.Front());
		}

		TEST_METHOD(SList_PushBack)
		{
			SiachenGameEngine::SList<char> list;

			// Pushing the first item
			char data = 'a';
			list.PushBack(data);
			Assert::AreEqual(data, list.Front());
			Assert::AreEqual(data, list.Back());

			// Pushing more items
			char data2 = 'b';
			list.PushBack(data2);
			Assert::AreEqual(data2, list.Back());

			char data3 = 'c';
			list.PushBack(data3);
			Assert::AreEqual(data3, list.Back());
		}

		TEST_METHOD(SList_PopFront)
		{
			SiachenGameEngine::SList<int32_t> list;

			list.PopFront();

			// Making the following list: 0 -> 5 -> 10 -> 15
			int32_t data1 = 5;
			list.PushBack(data1);
			int32_t data2 = 10;
			list.PushBack(data2);
			int32_t data3 = 15;
			list.PushBack(data3);
			int32_t data = 0;
			list.PushFront(data);

			Assert::AreEqual(list.Front(), 0);
			Assert::AreEqual(list.Back(), 15);
			Assert::AreEqual(list.Size(), 4);

			list.PopFront();
			Assert::AreEqual(list.Front(), 5);
			Assert::AreEqual(list.Size(), 3);

			list.PopFront();
			Assert::AreEqual(list.Front(), 10);
			Assert::AreEqual(list.Size(), 2);

			list.PopFront();
			Assert::AreEqual(list.Front(), 15);
			Assert::AreEqual(list.Size(), 1);

			list.PopFront();
			Assert::AreEqual(list.Size(), 0);
			Assert::AreEqual(list.IsEmpty(), true);
		}

		TEST_METHOD(SList_IsEmpty)
		{
			SiachenGameEngine::SList<int32_t> list;

			Assert::AreEqual(list.IsEmpty(), true);
			list.PushBack(10);
			Assert::AreEqual(list.IsEmpty(), false);
			list.PopFront();
			Assert::AreEqual(list.IsEmpty(), true);
		}

		TEST_METHOD(SList_Front)
		{
			SiachenGameEngine::SList<int32_t> list;

			// For no items
			auto expression = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(expression);

			// For the first item
			list.PushBack(10);
			Assert::AreEqual(list.Front(), 10);

			// For new item at the front
			list.PushFront(0);
			Assert::AreEqual(list.Front(), 0);

			// For removed item from front
			list.PopFront();
			Assert::AreEqual(list.Front(), 10);
		}

		TEST_METHOD(SList_Back)
		{
			SiachenGameEngine::SList<int32_t> list;

			// For no items
			auto expression = [&list] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(expression);

			// For the first item
			list.PushBack(10);
			Assert::AreEqual(list.Back(), 10);

			// For new item at the back
			list.PushBack(0);
			Assert::AreEqual(list.Back(), 0);
		}

		TEST_METHOD(SList_Size)
		{
			SiachenGameEngine::SList<int32_t> list;

			// When the list is empty
			Assert::AreEqual(list.Size(), 0);

			list.PushBack(10);
			Assert::AreEqual(list.Size(), 1);

			list.PushFront(0);
			Assert::AreEqual(list.Size(), 2);

			list.PopFront();
			Assert::AreEqual(list.Size(), 1);

			list.PopFront();
			Assert::AreEqual(list.Size(), 0);
		}

		TEST_METHOD(SList_Clean)
		{
			SiachenGameEngine::SList<int32_t> list;

			int32_t data = 5;
			
			list.PushFront(data);
			Assert::AreEqual(data, list.Front());
			Assert::AreEqual(data, list.Back());
			
			list.Clear();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}