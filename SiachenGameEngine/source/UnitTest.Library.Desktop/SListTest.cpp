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
			int32_t zero = 0, one = 1, two = 2;

			SiachenGameEngine::SList<int32_t> intList;

			// Testing initialization for list of integers
			Assert::AreEqual(intList.IsEmpty(), true);
			auto expression = [&intList] { intList.Front(); };
			Assert::ExpectException<std::runtime_error>(expression);
			auto expression3 = [&intList] { intList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression3);
			
			// Testing copy constructor after making a list
			intList.PushBack(one);
			intList.PushBack(two);
			intList.PushFront(zero);
			SiachenGameEngine::SList<int32_t> intList2(intList);
			Assert::AreEqual(intList2.Front(), 0);
			Assert::AreEqual(intList2.Back(), 2);
			Assert::AreEqual(intList2.Size(), 3);
			
			SiachenGameEngine::SList<int32_t*> intPtrList;

			// Testing initialization for list of pointers
			Assert::AreEqual(intPtrList.IsEmpty(), true);
			auto expression2 = [&intPtrList] {intPtrList.Front(); };
			Assert::ExpectException<std::runtime_error>(expression2);
			auto expression4 = [&intPtrList] {intPtrList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression4);
			
			// Testing copy constructor after making a list
			intPtrList.PushBack(&one);
			intPtrList.PushBack(&two);
			intPtrList.PushFront(&zero);
			SiachenGameEngine::SList<int32_t*> intPtrList2(intPtrList);
			Assert::AreEqual(intPtrList2.Front(), &zero);
			Assert::AreEqual(intPtrList2.Back(), &two);
			Assert::AreEqual(intPtrList2.Size(), 3);
		}

		TEST_METHOD(SList_PushFront)
		{
			int32_t data = 5, data2 = 10, data3 = 15;

			SiachenGameEngine::SList<int32_t> intList;
			// Pushing items into an empty list
			intList.PushFront(data);
			Assert::AreEqual(data, intList.Front());
			Assert::AreEqual(data, intList.Back());
			// Pushing items to non-empty list
			intList.PushFront(data2);
			Assert::AreEqual(data2, intList.Front());
			intList.PushFront(data3);
			Assert::AreEqual(data3, intList.Front());

			SiachenGameEngine::SList<int32_t*> intPtrList;
			// Pushing items into an empty list
			intPtrList.PushFront(&data);
			Assert::AreEqual(&data, intPtrList.Front());
			Assert::AreEqual(&data, intPtrList.Back());
			// Pushing items to non-empty list
			intPtrList.PushFront(&data2);
			Assert::AreEqual(&data2, intPtrList.Front());
			intPtrList.PushFront(&data3);
			Assert::AreEqual(&data3, intPtrList.Front());
		}

		TEST_METHOD(SList_PushBack)
		{
			int32_t data = 0, data2 = 1;
			
			SiachenGameEngine::SList<int32_t> intList;
			// Pushing items into an empty list
			intList.PushBack(data);
			Assert::AreEqual(data, intList.Front());
			Assert::AreEqual(data, intList.Back());
			// Pushing items to non-empty list
			intList.PushBack(data2);
			Assert::AreEqual(data2, intList.Back());
			
			SiachenGameEngine::SList<int32_t*> intPtrList;
			// Pushing items into an empty list
			intPtrList.PushBack(&data);
			Assert::AreEqual(&data, intPtrList.Front());
			Assert::AreEqual(&data, intPtrList.Back());
			// Pushing items to non-empty list
			intPtrList.PushBack(&data2);
			Assert::AreEqual(&data2, intPtrList.Back());
		}

		TEST_METHOD(SList_PopFront)
		{
			int32_t data = 0, data1 = 5;

			SiachenGameEngine::SList<int32_t> intList;
			// Pop for an empty list
			intList.PopFront();
			// Pop for an non-empty list till it has no items left
			intList.PushBack(data1);
			intList.PushFront(data);
			Assert::AreEqual(intList.Front(), data);
			Assert::AreEqual(intList.Size(), 2);
			intList.PopFront();
			Assert::AreEqual(intList.Front(), data1);
			Assert::AreEqual(intList.Size(), 1);
			intList.PopFront();
			Assert::AreEqual(intList.IsEmpty(), true);

			SiachenGameEngine::SList<int32_t*> intPtrList;
			// Pop for an empty list
			intPtrList.PopFront();
			// Pop for an non-empty list till it has no items left
			intPtrList.PushBack(&data1);
			intPtrList.PushFront(&data);
			Assert::AreEqual(intPtrList.Front(), &data);
			Assert::AreEqual(intPtrList.Size(), 2);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.Front(), &data1);
			Assert::AreEqual(intPtrList.Size(), 1);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.IsEmpty(), true);
		}

		TEST_METHOD(SList_IsEmpty)
		{
			int data = 10;

			SiachenGameEngine::SList<int32_t> intList;
			Assert::AreEqual(intList.IsEmpty(), true);
			intList.PushBack(data);
			Assert::AreEqual(intList.IsEmpty(), false);
			intList.PopFront();
			Assert::AreEqual(intList.IsEmpty(), true);

			SiachenGameEngine::SList<int32_t*> intPtrList;
			Assert::AreEqual(intPtrList.IsEmpty(), true);
			intPtrList.PushBack(&data);
			Assert::AreEqual(intPtrList.IsEmpty(), false);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.IsEmpty(), true);
		}

		TEST_METHOD(SList_Front)
		{
			int data = 0, data2 = 10;

			SiachenGameEngine::SList<int32_t> intList;
			// In case the list is empty
			auto expression = [&intList] {intList.Front(); };
			Assert::ExpectException<std::runtime_error>(expression);
			// In case the list isn't empty
			intList.PushBack(data2);
			Assert::AreEqual(intList.Front(), data2);
			intList.PushFront(data);
			Assert::AreEqual(intList.Front(), data);
			intList.PopFront();
			Assert::AreEqual(intList.Front(), data2);

			SiachenGameEngine::SList<int32_t*> intPtrList;
			// In case the list is empty
			auto expression2 = [&intPtrList] {intPtrList.Front(); };
			Assert::ExpectException<std::runtime_error>(expression2);
			// In case the list isn't empty
			intPtrList.PushBack(&data2);
			Assert::AreEqual(intPtrList.Front(), &data2);
			intPtrList.PushFront(&data);
			Assert::AreEqual(intPtrList.Front(), &data);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.Front(), &data2);
		}

		TEST_METHOD(SList_Back)
		{
			int data = 0, data2 = 10;

			SiachenGameEngine::SList<int32_t> intList;
			// If the list is empty
			auto expression = [&intList] {intList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression);
			// If the list isn't empty
			intList.PushBack(data2);
			Assert::AreEqual(intList.Back(), data2);
			intList.PushBack(data);
			Assert::AreEqual(intList.Back(), data);

			SiachenGameEngine::SList<int32_t*> intPtrList;
			// If the list is empty
			auto expression2 = [&intPtrList] {intPtrList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression2);
			// If the list isn't empty
			intPtrList.PushBack(&data2);
			Assert::AreEqual(intPtrList.Back(), &data2);
			intPtrList.PushBack(&data);
			Assert::AreEqual(intPtrList.Back(), &data);
		}

		TEST_METHOD(SList_Size)
		{
			int data = 0, data2 = 10;

			SiachenGameEngine::SList<int32_t> intList;
			// If the list is empty
			Assert::AreEqual(intList.Size(), 0);
			// If the list isn't empty
			intList.PushBack(data2);
			Assert::AreEqual(intList.Size(), 1);
			intList.PushFront(data);
			Assert::AreEqual(intList.Size(), 2);
			intList.PopFront();
			Assert::AreEqual(intList.Size(), 1);

			SiachenGameEngine::SList<int32_t*> intPtrList;
			// If the list is empty
			Assert::AreEqual(intPtrList.Size(), 0);
			// If the list isn't empty
			intPtrList.PushBack(&data2);
			Assert::AreEqual(intPtrList.Size(), 1);
			intPtrList.PushFront(&data);
			Assert::AreEqual(intPtrList.Size(), 2);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.Size(), 1);
		}

		TEST_METHOD(SList_AssignmentOperator)
		{
			int data = 5, data2 = 10;
			// Assignment operator for lists of integers
			SiachenGameEngine::SList<int32_t> intListLHS;
			SiachenGameEngine::SList<int32_t> intListRHS;
			intListLHS.PushFront(data);
			intListLHS.PushFront(data2);
			intListRHS.PushFront(data2);
			intListRHS.PushFront(data);
			intListLHS = intListRHS;
			Assert::AreEqual(intListLHS.Front(), data);
			Assert::AreEqual(intListLHS.Back(), data2);
			// Assignment operator for lists of pointers to integers
			SiachenGameEngine::SList<int32_t*> intPtrListLHS;
			SiachenGameEngine::SList<int32_t*> intPtrListRHS;
			intPtrListLHS.PushFront(&data);
			intPtrListLHS.PushFront(&data2);
			intPtrListRHS.PushFront(&data2);
			intPtrListRHS.PushFront(&data);
			intPtrListLHS = intPtrListRHS;
			Assert::AreEqual(intPtrListLHS.Front(), &data);
			Assert::AreEqual(intPtrListLHS.Back(), &data2);
		}

		TEST_METHOD(SList_Clear)
		{
			int32_t data = 5;
			
			SiachenGameEngine::SList<int32_t> intList;
			intList.PushFront(data);
			intList.Clear();

			SiachenGameEngine::SList<int32_t*> intPtrList;
			intPtrList.PushFront(&data);
			intPtrList.Clear();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}