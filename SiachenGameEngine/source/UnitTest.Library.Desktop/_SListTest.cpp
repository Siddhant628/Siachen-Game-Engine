#include "pch.h"
#include "CppUnitTest.h"
#include "_SList.h"
#include <stdexcept>

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

		TEST_METHOD(_SList_Constructors)
		{
			// Default constructor
			SiachenGameEngine::_SList _list;
			Assert::AreEqual(_list.IsEmpty(), true);

			auto expression = [&_list] { _list.Front(); };
			Assert::ExpectException<std::runtime_error>(expression);

			auto expression2 = [&_list] { _list.Back(); };
			Assert::ExpectException<std::runtime_error>(expression2);

			// Copy constructor
			_list.PushBack(1);
			_list.PushBack(2);
			_list.PushBack(3);
			_list.PushFront(0);

			SiachenGameEngine::_SList _list2(_list);

			Assert::AreEqual(_list2.Front(), 0);
			Assert::AreEqual(_list2.Back(), 3);
			Assert::AreEqual(_list2.Size(), 4);
		}

		TEST_METHOD(_SList_PushFront)
		{
			SiachenGameEngine::_SList _list;

			// Pushing the first item
			int32_t data = 5;
			_list.PushFront(data);
			Assert::AreEqual(data, _list.Front());
			Assert::AreEqual(data, _list.Back());

			// Pushing more items
			int32_t data2 = 10;
			_list.PushFront(data2);
			Assert::AreEqual(data2, _list.Front());

			int32_t data3 = 15;
			_list.PushFront(data3);
			Assert::AreEqual(data3, _list.Front());
		}

		TEST_METHOD(_SList_PushBack)
		{
			SiachenGameEngine::_SList _list;

			// Pushing the first item
			int32_t data = 5;
			_list.PushBack(data);
			Assert::AreEqual(data, _list.Front());
			Assert::AreEqual(data, _list.Back());

			// Pushing more items
			int32_t data2 = 10;
			_list.PushBack(data2);
			Assert::AreEqual(data2, _list.Back());

			int32_t data3 = 15;
			_list.PushBack(data3);
			Assert::AreEqual(data3, _list.Back());
		}

		TEST_METHOD(_SList_PopFront)
		{
			SiachenGameEngine::_SList _list;

			_list.PopFront();

			// Making the following list: 0 -> 5 -> 10 -> 15
			int32_t data1 = 5;
			_list.PushBack(data1);
			int32_t data2 = 10;
			_list.PushBack(data2);
			int32_t data3 = 15;
			_list.PushBack(data3);
			int32_t data = 0;
			_list.PushFront(data);

			Assert::AreEqual(_list.Front(), 0);
			Assert::AreEqual(_list.Back(), 15);
			Assert::AreEqual(_list.Size(), 4);

			_list.PopFront();
			Assert::AreEqual(_list.Front(), 5);
			Assert::AreEqual(_list.Size(), 3);

			_list.PopFront();
			Assert::AreEqual(_list.Front(), 10);
			Assert::AreEqual(_list.Size(), 2);

			_list.PopFront();
			Assert::AreEqual(_list.Front(), 15);
			Assert::AreEqual(_list.Size(), 1);

			_list.PopFront();
			Assert::AreEqual(_list.Size(), 0);
			Assert::AreEqual(_list.IsEmpty(), true);
		}

		TEST_METHOD(_SList_IsEmpty)
		{
			SiachenGameEngine::_SList _list;

			Assert::AreEqual(_list.IsEmpty(), true);
			_list.PushBack(10);
			Assert::AreEqual(_list.IsEmpty(), false);
			_list.PopFront();
			Assert::AreEqual(_list.IsEmpty(), true);
		}

		TEST_METHOD(_SList_Front)
		{
			SiachenGameEngine::_SList _list;
			
			// For no items
			auto expression = [&_list] {_list.Front(); };
			Assert::ExpectException<std::runtime_error>(expression);
			
			// For the first item
			_list.PushBack(10);
			Assert::AreEqual(_list.Front(), 10);

			// For new item at the front
			_list.PushFront(0);
			Assert::AreEqual(_list.Front(), 0);

			// For removed item from front
			_list.PopFront();
			Assert::AreEqual(_list.Front(), 10);
		}

		TEST_METHOD(_SList_Back)
		{
			SiachenGameEngine::_SList _list;

			// For no items
			auto expression = [&_list] {_list.Back(); };
			Assert::ExpectException<std::runtime_error>(expression);

			// For the first item
			_list.PushBack(10);
			Assert::AreEqual(_list.Back(), 10);

			// For new item at the back
			_list.PushBack(0);
			Assert::AreEqual(_list.Back(), 0);
		}

		TEST_METHOD(_SList_Size)
		{
			SiachenGameEngine::_SList _list;

			// When the list is empty
			Assert::AreEqual(_list.Size(), 0);

			_list.PushBack(10);
			Assert::AreEqual(_list.Size(), 1);

			_list.PushFront(0);
			Assert::AreEqual(_list.Size(), 2);

			_list.PopFront();
			Assert::AreEqual(_list.Size(), 1);

			_list.PopFront();
			Assert::AreEqual(_list.Size(), 0);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState _SListTest::sStartMemState;
}