#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

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

			SList<int32_t> intList;
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
			SList<int32_t> intList2(intList);
			Assert::AreEqual(intList2.Front(), 0);
			Assert::AreEqual(intList2.Back(), 2);
			Assert::AreEqual(intList2.Size(), 3);

			SList<int32_t*> intPtrList;
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
			SList<int32_t*> intPtrList2(intPtrList);
			Assert::AreEqual(intPtrList2.Front(), &zero);
			Assert::AreEqual(intPtrList2.Back(), &two);
			Assert::AreEqual(intPtrList2.Size(), 3);

			SList<Foo> fooList;
			// Testing initialization for list of Foos
			Assert::AreEqual(fooList.IsEmpty(), true);
			auto expression5 = [&fooList] {fooList.Front(); };
			Assert::ExpectException<std::runtime_error>(expression5);
			auto expression6 = [&fooList] {fooList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression6);
			// Testing copy constructor
			Foo fooZero(zero), fooOne(one), fooTwo(two);
			fooList.PushBack(fooOne);
			fooList.PushBack(fooTwo);
			fooList.PushFront(fooZero);
			SList<Foo> fooList2(fooList);
			Assert::AreEqual(fooZero, fooList2.Front());
			Assert::AreEqual(fooTwo, fooList2.Back());
			Assert::AreEqual(fooList2.Size(), 3);
		}

		TEST_METHOD(SList_PushFront)
		{
			int32_t data = 5, data2 = 10, data3 = 15;

			SList<int32_t> intList;
			// Pushing items into an empty list
			SList<int32_t>::Iterator it = intList.PushFront(data);
			Assert::AreEqual(*it, intList.Front());
			Assert::AreEqual(data, intList.Front());
			Assert::AreEqual(data, intList.Back());
			// Pushing items to non-empty list
			SList<int32_t>::Iterator it2 = intList.PushFront(data2);
			Assert::AreEqual(*it2, intList.Front());
			Assert::AreEqual(data2, intList.Front());
			intList.PushFront(data3);
			Assert::AreEqual(data3, intList.Front());

			SList<int32_t*> intPtrList;
			// Pushing items into an empty list
			SList<int32_t*>::Iterator it3 = intPtrList.PushFront(&data);
			Assert::AreEqual(*it3, intPtrList.Front());
			Assert::AreEqual(&data, intPtrList.Front());
			Assert::AreEqual(&data, intPtrList.Back());
			// Pushing items to non-empty list
			SList<int32_t*>::Iterator it4 = intPtrList.PushFront(&data2);
			Assert::AreEqual(*it4, intPtrList.Front());
			Assert::AreEqual(&data2, intPtrList.Front());
			intPtrList.PushFront(&data3);
			Assert::AreEqual(&data3, intPtrList.Front());

			SList<Foo> fooList;
			Foo fooFive(data), fooTen(data2), fooFifteen(data3);
			// Pushing items into an empty list
			SList<Foo>::Iterator it5 = fooList.PushFront(fooFive);
			Assert::AreEqual(*it5, fooList.Front());
			Assert::AreEqual(fooFive, fooList.Front());
			Assert::AreEqual(fooFive, fooList.Back());
			// Pushing items to non-empty list
			SList<Foo>::Iterator it6 = fooList.PushFront(fooTen);
			Assert::AreEqual(*it6, fooList.Front());
			Assert::AreEqual(fooTen, fooList.Front());
			fooList.PushFront(fooFifteen);
			Assert::AreEqual(fooFifteen, fooList.Front());
		}

		TEST_METHOD(SList_PushBack)
		{
			int32_t data = 0, data2 = 1;

			SList<int32_t> intList;
			// Pushing items into an empty list
			SList<int32_t>::Iterator it = intList.PushBack(data);
			Assert::AreEqual(*it, intList.Back());
			Assert::AreEqual(data, intList.Front());
			Assert::AreEqual(data, intList.Back());
			// Pushing items to non-empty list
			SList<int32_t>::Iterator it2 = intList.PushBack(data2);
			Assert::AreEqual(*it2, intList.Back());
			Assert::AreEqual(data2, intList.Back());

			SList<int32_t*> intPtrList;
			// Pushing items into an empty list
			SList<int32_t*>::Iterator it3 = intPtrList.PushBack(&data);
			Assert::AreEqual(*it3, intPtrList.Back());
			Assert::AreEqual(&data, intPtrList.Front());
			Assert::AreEqual(&data, intPtrList.Back());
			// Pushing items to non-empty list
			SList<int32_t*>::Iterator it4 = intPtrList.PushBack(&data2);
			Assert::AreEqual(*it4, intPtrList.Back());
			Assert::AreEqual(&data2, intPtrList.Back());

			SList<Foo> fooList;
			Foo fooZero(data), fooOne(data2);
			// Pushing items into an empty list
			SList<Foo>::Iterator it5 = fooList.PushBack(fooZero);
			Assert::AreEqual(*it5, fooList.Back());
			Assert::AreEqual(fooZero, fooList.Front());
			Assert::AreEqual(fooZero, fooList.Back());
			// Pushing items to non-empty list
			SList<Foo>::Iterator it6 = fooList.PushBack(fooOne);
			Assert::AreEqual(*it6, fooList.Back());
			Assert::AreEqual(fooOne, fooList.Back());
		}

		TEST_METHOD(SList_PopFront)
		{
			int32_t data = 0, data1 = 5;

			SList<int32_t> intList;
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

			SList<int32_t*> intPtrList;
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

			SList<Foo> fooList;
			Foo fooZero(data), fooFive(data1);
			// Pop for an empty list
			fooList.PopFront();
			// Pop for an non-empty list till it has no items left
			fooList.PushBack(fooFive);
			fooList.PushFront(fooZero);
			Assert::AreEqual(fooList.Front(), fooZero);
			Assert::AreEqual(fooList.Size(), 2);
			fooList.PopFront();
			Assert::AreEqual(fooList.Front(), fooFive);
			Assert::AreEqual(fooList.Size(), 1);
			fooList.PopFront();
			Assert::AreEqual(fooList.IsEmpty(), true);
		}

		TEST_METHOD(SList_IsEmpty)
		{
			int data = 10;

			SList<int32_t> intList;
			Assert::AreEqual(intList.IsEmpty(), true);
			intList.PushBack(data);
			Assert::AreEqual(intList.IsEmpty(), false);
			intList.PopFront();
			Assert::AreEqual(intList.IsEmpty(), true);

			SList<int32_t*> intPtrList;
			Assert::AreEqual(intPtrList.IsEmpty(), true);
			intPtrList.PushBack(&data);
			Assert::AreEqual(intPtrList.IsEmpty(), false);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.IsEmpty(), true);

			SList<Foo> fooList;
			Foo fooTen(data);
			Assert::AreEqual(fooList.IsEmpty(), true);
			fooList.PushBack(fooTen);
			Assert::AreEqual(fooList.IsEmpty(), false);
			fooList.PopFront();
			Assert::AreEqual(fooList.IsEmpty(), true);
		}

		TEST_METHOD(SList_Front)
		{
			int data = 0, data2 = 10;

			SList<int32_t> intList;
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
			// Modifying front
			intList.Front() = data;
			Assert::AreEqual(intList.Front(), data);
			// Testing const function
			intList.PushBack(data);
			intList.PushBack(data2);
			const SList<int32_t> intList2(intList);
			Assert::AreEqual(intList2.Front(), data);

			SList<int32_t*> intPtrList;
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
			// Modifying front
			intPtrList.Front() = &data;
			Assert::AreEqual(intPtrList.Front(), &data);
			// Testing const function
			intPtrList.PushBack(&data);
			intPtrList.PushBack(&data2);
			const SList<int32_t*> intPtrList2(intPtrList);
			Assert::AreEqual(intPtrList.Front(), &data);

			SList<Foo> fooList;
			Foo fooZero(data), fooTen(data2);
			// In case the list is empty
			auto expression3 = [&fooList] {fooList.Front(); };
			Assert::ExpectException<std::runtime_error>(expression3);
			// In case the list isn't empty
			fooList.PushBack(fooTen);
			Assert::AreEqual(fooList.Front(), fooTen);
			fooList.PushFront(fooZero);
			Assert::AreEqual(fooList.Front(), fooZero);
			fooList.PopFront();
			Assert::AreEqual(fooList.Front(), fooTen);
			// Modifying front
			fooList.Front() = fooZero;
			Assert::AreEqual(fooList.Front(), fooZero);
			// Testing const function
			fooList.PushBack(fooTen);
			fooList.PushFront(fooZero);
			const SList<Foo> fooList2(fooList);
			Assert::AreEqual(fooList2.Front(), fooZero);

		}

		TEST_METHOD(SList_Back)
		{
			int data = 0, data2 = 10;

			SList<int32_t> intList;
			// If the list is empty
			auto expression = [&intList] {intList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression);
			// If the list isn't empty
			intList.PushBack(data2);
			Assert::AreEqual(intList.Back(), data2);
			intList.PushBack(data);
			Assert::AreEqual(intList.Back(), data);
			// Modifying back
			intList.Back() = data2;
			Assert::AreEqual(intList.Back(), data2);
			// Testing const function
			intList.PushBack(data);
			intList.PushBack(data2);
			const SList<int32_t> intList2(intList);
			Assert::AreEqual(intList2.Back(), data2);

			SList<int32_t*> intPtrList;
			// If the list is empty
			auto expression2 = [&intPtrList] {intPtrList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression2);
			// If the list isn't empty
			intPtrList.PushBack(&data2);
			Assert::AreEqual(intPtrList.Back(), &data2);
			intPtrList.PushBack(&data);
			Assert::AreEqual(intPtrList.Back(), &data);
			// Modifying back
			intPtrList.Back() = &data2;
			Assert::AreEqual(intPtrList.Back(), &data2);
			// Testing const function
			intPtrList.PushBack(&data);
			intPtrList.PushBack(&data2);
			const SList<int32_t*> intPtrList2(intPtrList);
			Assert::AreEqual(intPtrList.Back(), &data2);

			SList<Foo> fooList;
			Foo fooZero(data), fooTen(data2);
			// If the list is empty
			auto expression3 = [&fooList] {fooList.Back(); };
			Assert::ExpectException<std::runtime_error>(expression3);
			// If the list isn't empty
			fooList.PushBack(fooTen);
			Assert::AreEqual(fooList.Back(), fooTen);
			fooList.PushBack(fooZero);
			Assert::AreEqual(fooList.Back(), fooZero);
			// Modifying back
			fooList.Back() = fooTen;
			Assert::AreEqual(fooList.Back(), fooTen);
			// Testing const function
			fooList.PushBack(fooTen);
			fooList.PushFront(fooZero);
			const SList<Foo> fooList2(fooList);
			Assert::AreEqual(fooList2.Back(), fooTen);
		}

		TEST_METHOD(SList_Size)
		{
			int data = 0, data2 = 10;

			SList<int32_t> intList;
			// If the list is empty
			Assert::AreEqual(intList.Size(), 0);
			// If the list isn't empty
			intList.PushBack(data2);
			Assert::AreEqual(intList.Size(), 1);
			intList.PushFront(data);
			Assert::AreEqual(intList.Size(), 2);
			intList.PopFront();
			Assert::AreEqual(intList.Size(), 1);

			SList<int32_t*> intPtrList;
			// If the list is empty
			Assert::AreEqual(intPtrList.Size(), 0);
			// If the list isn't empty
			intPtrList.PushBack(&data2);
			Assert::AreEqual(intPtrList.Size(), 1);
			intPtrList.PushFront(&data);
			Assert::AreEqual(intPtrList.Size(), 2);
			intPtrList.PopFront();
			Assert::AreEqual(intPtrList.Size(), 1);

			SList<Foo> fooList;
			Foo fooZero(data), fooTen(data2);
			// If the list is empty
			Assert::AreEqual(fooList.Size(), 0);
			// If the list isn't empty
			fooList.PushBack(fooTen);
			Assert::AreEqual(fooList.Size(), 1);
			fooList.PushFront(fooZero);
			Assert::AreEqual(fooList.Size(), 2);
			fooList.PopFront();
			Assert::AreEqual(fooList.Size(), 1);
		}

		TEST_METHOD(SList_Assignment_Operator)
		{
			int data = 5, data2 = 10;
			// Assignment operator for lists of integers
			SList<int32_t> intListLHS;
			SList<int32_t> intListRHS;
			intListLHS.PushFront(data);
			intListLHS.PushFront(data2);
			intListRHS.PushFront(data2);
			intListRHS.PushFront(data);
			intListLHS = intListRHS;
			Assert::AreEqual(intListLHS.Front(), data);
			Assert::AreEqual(intListLHS.Back(), data2);

			// Assignment operator for lists of pointers to integers
			SList<int32_t*> intPtrListLHS;
			SList<int32_t*> intPtrListRHS;
			intPtrListLHS.PushFront(&data);
			intPtrListLHS.PushFront(&data2);
			intPtrListRHS.PushFront(&data2);
			intPtrListRHS.PushFront(&data);
			intPtrListLHS = intPtrListRHS;
			Assert::AreEqual(intPtrListLHS.Front(), &data);
			Assert::AreEqual(intPtrListLHS.Back(), &data2);

			// Assignment operator for lists of pointers to Foos
			Foo fooZero(data), fooTen(data2);
			SList<Foo> fooListLHS;
			SList<Foo> fooListRHS;
			fooListLHS.PushFront(fooZero);
			fooListLHS.PushFront(fooTen);
			fooListRHS.PushFront(fooTen);
			fooListRHS.PushFront(fooZero);
			fooListLHS = fooListRHS;
			Assert::AreEqual(fooListLHS.Front(), fooZero);
			Assert::AreEqual(fooListLHS.Back(), fooTen);
		}

		TEST_METHOD(SList_Clear)
		{
			int32_t data = 5;

			SList<int32_t> intList;
			intList.PushFront(data);
			intList.Clear();

			SList<int32_t*> intPtrList;
			intPtrList.PushFront(&data);
			intPtrList.Clear();

			Foo fooFive(data);
			SList<Foo> fooList;
			fooList.PushFront(fooFive);
			fooList.Clear();
		}

		TEST_METHOD(SList_Begin)
		{
			int data = 10;

			SList<int32_t> intList;
			// For empty list
			SList<int32_t>::Iterator it = intList.Begin();
			auto intExpression = [&it] { *it; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// For non-empty list
			SList<int32_t>::Iterator it2 = intList.PushFront(data);
			SList<int32_t>::Iterator it3 = intList.Begin();
			Assert::AreEqual(it2, it3);

			SList<int32_t*> intPtrList;
			// For empty list
			SList<int32_t*>::Iterator it4 = intPtrList.Begin();
			auto intPtrExpression = [&it4] { *it4; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// For non-empty list
			SList<int32_t*>::Iterator it5 = intPtrList.PushFront(&data);
			SList<int32_t*>::Iterator it6 = intPtrList.Begin();
			Assert::AreEqual(it5, it6);

			SList<Foo> fooList;
			Foo foo(data);
			// For empty list
			SList<Foo>::Iterator it7 = fooList.Begin();
			auto fooExpression = [&it7] { *it7; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// For non-empty list
			SList<Foo>::Iterator it8 = fooList.PushBack(foo);
			SList<Foo>::Iterator it9 = fooList.Begin();
			Assert::AreEqual(it8, it9);

		}

		TEST_METHOD(SList_End)
		{

			SList<int32_t> intList, otherIntList;
			SList<int32_t>::Iterator it = intList.End();
			auto intExpression = [&it] { *it; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			SList<int32_t>::Iterator it2 = otherIntList.End();
			Assert::AreNotEqual(it, it2);

			SList<int32_t*> intPtrList, otherIntPtrList;
			SList<int32_t*>::Iterator it3 = intPtrList.End();
			auto intPtrExpression = [&it3] { *it3; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			SList<int32_t*>::Iterator it4 = otherIntPtrList.End();
			Assert::AreNotEqual(it3, it4);

			SList<Foo> fooList, otherFooList;
			SList<Foo>::Iterator it5 = fooList.End();
			auto fooExpression = [&it5] { *it5; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			SList<Foo>::Iterator it6 = otherFooList.End();
			Assert::AreNotEqual(it5, it6);

		}

		TEST_METHOD(SList_InsertAfter)
		{
			int data = 10, data2;

			SList<int32_t> intList;
			SList<int32_t>::Iterator it;
			// When Iterator isn't owned by the list
			auto intExpression = [&intList, &data, &it] { intList.InsertAfter(data, it); };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// Regular insert
			SList<int32_t>::Iterator it2 = intList.PushBack(data);
			SList<int32_t>::Iterator it3 = intList.InsertAfter(data2, it2);
			Assert::AreEqual(data2, intList.Back());
			Assert::AreEqual(data2, *it3);
			// When inserting beyond the list
			auto intExpression2 = [&intList, &data, &it3] { intList.InsertAfter(data, ++it3);  };
			Assert::ExpectException<std::runtime_error>(intExpression2);

			SList<int32_t*> intPtrList;
			SList<int32_t*>::Iterator it4;
			// When Iterator isn't owned by the list
			auto intPtrExpression = [&intPtrList, &data, &it4] { intPtrList.InsertAfter(&data, it4); };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// Regular insert
			SList<int32_t*>::Iterator it5 = intPtrList.PushBack(&data);
			SList<int32_t*>::Iterator it6 = intPtrList.InsertAfter(&data2, it5);
			Assert::AreEqual(&data2, intPtrList.Back());
			Assert::AreEqual(&data2, *it6);
			// When inserting beyond the list
			auto intPtrExpression2 = [&intPtrList, &data, &it6] { intPtrList.InsertAfter(&data, ++it6);  };
			Assert::ExpectException<std::runtime_error>(intPtrExpression2);

			SList<Foo> fooList;
			Foo foo(data), foo2(data2);
			SList<Foo>::Iterator it7;
			// When Iterator isn't owned by the list
			auto fooExpression = [&fooList, &foo, &it7] { fooList.InsertAfter(foo, it7); };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// Regular insert
			SList<Foo>::Iterator it8 = fooList.PushBack(foo);
			SList<Foo>::Iterator it9 = fooList.InsertAfter(foo2, it8);
			Assert::AreEqual(foo2, fooList.Back());
			Assert::AreEqual(foo2, *it9);
			// When inserting beyond the list
			auto fooExpression2 = [&fooList, &foo, &it9] { fooList.InsertAfter(foo, ++it9);  };
			Assert::ExpectException<std::runtime_error>(fooExpression2);
		}

		TEST_METHOD(SList_Find)
		{
			int32_t data = 10, data2 = 20;

			SList<int32_t> intList;
			SList<int32_t>::Iterator it = intList.PushFront(data);
			SList<int32_t>::Iterator it2 = intList.Find(data2);
			auto intExpression = [&it2] { *it2; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			Assert::AreEqual(it, intList.Find(data));

			SList<int32_t*> intPtrList;
			SList<int32_t*>::Iterator it3 = intPtrList.PushFront(&data);
			SList<int32_t*>::Iterator it4 = intPtrList.Find(&data2);
			auto intPtrExpression = [&it4] { *it4; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			Assert::AreEqual(it3, intPtrList.Find(&data));

			SList<Foo> fooList;
			Foo foo(data), foo2(data2);
			SList<Foo>::Iterator it5 = fooList.PushFront(foo);
			SList<Foo>::Iterator it6 = fooList.Find(foo2);
			auto fooExpression = [&it6] { *it6; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			Assert::AreEqual(it5, fooList.Find(foo));
		}
	
		TEST_METHOD(SList_Remove)
		{
			int32_t data = 10, data2 = 20, data3 = 30;

			SList<int32_t> intList;
			// When item is absent
			Assert::IsFalse(intList.Remove(data));
			// Removing last item
			intList.PushBack(data);
			intList.PushBack(data2);
			intList.PushBack(data3);
			Assert::IsTrue(intList.Remove(data3));
			Assert::AreEqual(intList.Back(), data2);
			// Removing intermediate item
			intList.PushBack(data3);
			Assert::IsTrue(intList.Remove(data2));
			
			SList<int32_t*> intPtrList;
			// When item is absent
			Assert::IsFalse(intPtrList.Remove(&data));
			// Removing last item
			intPtrList.PushBack(&data);
			intPtrList.PushBack(&data2);
			intPtrList.PushBack(&data3);
			Assert::IsTrue(intPtrList.Remove(&data3));
			Assert::AreEqual(intPtrList.Back(), &data2);
			// Removing intermediate item
			intPtrList.PushBack(&data3);
			Assert::IsTrue(intPtrList.Remove(&data2));

			SList<Foo> fooList;
			Foo foo(data), foo2(data2), foo3(data3);
			// When item is absent
			Assert::IsFalse(fooList.Remove(foo));
			// Removing last item
			fooList.PushBack(foo);
			fooList.PushBack(foo2);
			fooList.PushBack(foo3);
			Assert::IsTrue(fooList.Remove(foo3));
			Assert::AreEqual(fooList.Back(), foo2);
			// Removing intermediate item
			fooList.PushBack(foo3);
			Assert::IsTrue(fooList.Remove(foo2));
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}