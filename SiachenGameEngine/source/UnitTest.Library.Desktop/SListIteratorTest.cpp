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
	TEST_CLASS(SListIteratorTest)
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

		TEST_METHOD(Iterator_Constructors)
		{
			int32_t data = 10, data2 = 20;

			// Default constructor
			SList<int32_t>::Iterator it, it2;
			Assert::AreEqual(it, it2);
			auto intExpression = [&it] { it++; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			auto intExpression2 = [&it2] { ++it2; };
			Assert::ExpectException<std::runtime_error>(intExpression2);
			auto intExpression3 = [&it2] { *it2; };
			Assert::ExpectException<std::runtime_error>(intExpression3);
			// Copy constructor
			SList<int32_t> intList;
			intList.PushBack(data2);
			SList<int32_t>::Iterator intItFront = intList.PushFront(data);
			SList<int32_t>::Iterator it3(intItFront);
			Assert::AreEqual(intItFront, it3);
			Assert::AreEqual(*it3, data);
			Assert::AreNotEqual(intItFront, it2);

			// Default constructor
			SList<int32_t*>::Iterator it4, it5;
			Assert::AreEqual(it4, it5);
			auto intPrtExpression = [&it4] { it4++; };
			Assert::ExpectException<std::runtime_error>(intPrtExpression);
			auto intPrtExpression2 = [&it5] { ++it5; };
			Assert::ExpectException<std::runtime_error>(intPrtExpression2);
			auto intPrtExpression3 = [&it5] { *it5; };
			Assert::ExpectException<std::runtime_error>(intPrtExpression3);
			// Copy constructor
			SList<int32_t*> intPtrList;
			intPtrList.PushBack(&data2);
			SList<int32_t*>::Iterator it6 = intPtrList.PushFront(&data);
			SList<int32_t*>::Iterator it7(it6);
			Assert::AreEqual(it6, it7);
			Assert::AreEqual(*it7, &data);

			// Default constructor
			SList<Foo>::Iterator it8, it9;
			Assert::AreEqual(it8, it9);
			auto fooExpression = [&it8] { it8++; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			auto fooExpression2 = [&it9] { ++it9; };
			Assert::ExpectException<std::runtime_error>(fooExpression2);
			auto fooExpression3 = [&it9] { *it9; };
			Assert::ExpectException<std::runtime_error>(fooExpression3);
			// Copy constructor
			Foo foo(data), foo2(data2);
			SList<Foo> fooList;
			fooList.PushBack(foo2);
			SList<Foo>::Iterator it10 = fooList.PushFront(foo);
			SList<Foo>::Iterator it11(it10);
			Assert::AreEqual(it10, it11);
			Assert::AreEqual(*it11, foo);

		}

		TEST_METHOD(Iterator_Assignment_Operator)
		{
			int32_t data = 10, data2 = 20;
			
			SList<int32_t> intList;
			SList<int32_t>::Iterator it = intList.PushFront(data);
			SList<int32_t>::Iterator it2 = intList.PushBack(data2);
			Assert::AreNotEqual(it, it2);
			Assert::AreEqual(*it, data);
			Assert::AreEqual(*it2, data2);
			it2 = it;
			Assert::AreEqual(it, it2);
			Assert::AreEqual(*it2, data);

			SList<int32_t*> intPtrList;
			SList<int32_t*>::Iterator it3 = intPtrList.PushFront(&data);
			SList<int32_t*>::Iterator it4 = intPtrList.PushBack(&data2);
			Assert::AreNotEqual(it3, it4);
			Assert::AreEqual(*it3, &data);
			Assert::AreEqual(*it4, &data2);
			it4 = it3;
			Assert::AreEqual(it3, it4);
			Assert::AreEqual(*it4, &data);

			SList<Foo> fooList;
			Foo foo(data), foo2(data2);
			SList<Foo>::Iterator it5 = fooList.PushFront(foo);
			SList<Foo>::Iterator it6 = fooList.PushBack(foo2);
			Assert::AreNotEqual(it5, it6);
			Assert::AreEqual(*it5, foo);
			Assert::AreEqual(*it6, foo2);
			it6 = it5;
			Assert::AreEqual(it5, it6);
			Assert::AreEqual(*it6, foo);
		}

		TEST_METHOD(Iterator_Equals_Operator) 
		{
			int32_t data = 10, data2 = 20;

			SList<int32_t> intList, otherIntList;
			SList<int32_t>::Iterator it, it2, it3;
			Assert::AreEqual(it, it2);
			it = intList.PushFront(data);
			it2 = intList.PushBack(data2);
			Assert::AreNotEqual(it, it2);
			it = it2;
			Assert::AreEqual(it, it2);
			it3 = otherIntList.PushFront(data);
			Assert::AreNotEqual(it, it3);
			

			SList<int32_t*> intPtrList, otherIntPtrList;
			SList<int32_t*>::Iterator it4, it5, it6;
			Assert::AreEqual(it4, it5);
			it4 = intPtrList.PushFront(&data);
			it5 = intPtrList.PushBack(&data2);
			Assert::AreNotEqual(it4, it5);
			it4 = it5;
			Assert::AreEqual(it4, it5);
			it6 = otherIntPtrList.PushFront(&data);
			Assert::AreNotEqual(it4, it6);

			SList<Foo> fooList, otherFooList;
			Foo foo(data), foo2(data2);
			SList<Foo>::Iterator it7, it8, it9;
			Assert::AreEqual(it7, it8);
			it7 = fooList.PushFront(foo);
			it8 = fooList.PushBack(foo2);
			Assert::AreNotEqual(it7, it8);
			it7 = it8;
			Assert::AreEqual(it7, it8);
			it9 = otherFooList.PushFront(foo);
			Assert::AreNotEqual(it7, it9);
		}

		TEST_METHOD(Iterator_Inequals_Operator) 
		{
			int32_t data = 10, data2 = 20;

			SList<int32_t> intList, otherIntList;
			SList<int32_t>::Iterator it, it2, it3;
			Assert::IsFalse(it != it2);		
			it = intList.PushFront(data);
			it2 = intList.PushBack(data2);
			Assert::IsTrue(it != it2);
			it3 = otherIntList.PushFront(data);
			Assert::IsTrue(it != it3);

			SList<int32_t*> intPtrList, otherIntPtrList;
			SList<int32_t*>::Iterator it4, it5, it6;
			Assert::IsFalse(it4 != it5);
			it4 = intPtrList.PushFront(&data);
			it5 = intPtrList.PushBack(&data2);
			Assert::IsTrue(it4 != it5);
			it6 = otherIntPtrList.PushFront(&data);
			Assert::IsTrue(it4 != it6);

			SList<Foo> fooList, otherFooList;
			Foo foo(data), foo2(data2);
			SList<Foo>::Iterator it7, it8, it9;
			Assert::IsFalse(it7 != it8);
			it7 = fooList.PushFront(foo);
			it8 = fooList.PushBack(foo2);
			Assert::IsTrue(it7 != it8);
			it9 = otherFooList.PushFront(foo);
			Assert::IsTrue(it7 != it9);
		}

		TEST_METHOD(Iterator_PreIncrement_Operator)
		{
			int32_t data = 10, data2 = 20;

			SList<int32_t> intList;
			intList.PushFront(data);
			intList.PushBack(data2);
			SList<int32_t>::Iterator it;
			auto intExpression = [&it] { ++it; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			it = intList.begin();
			Assert::AreEqual(*(++it), data2);
			Assert::AreEqual(*it, data2);

			SList<int32_t*> intPtrList;
			intPtrList.PushFront(&data);
			intPtrList.PushBack(&data2);
			SList<int32_t*>::Iterator it2;
			auto intPtrExpression = [&it2] { ++it2; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			it2 = intPtrList.begin();
			Assert::AreEqual(*(++it2), &data2);
			Assert::AreEqual(*it2, &data2);

			SList<Foo> fooList;
			Foo foo(data), foo2(data2);
			fooList.PushFront(foo);
			fooList.PushBack(foo2);
			SList<Foo>::Iterator it3;
			auto fooExpression = [&it3] { ++it3; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			it3 = fooList.begin();
			Assert::AreEqual(*(++it3), foo2);
			Assert::AreEqual(*it3, foo2);
		}

		TEST_METHOD(Iterator_PostIncrement_Operator)
		{
			int32_t data = 10, data2 = 20;

			SList<int32_t> intList;
			intList.PushFront(data);
			intList.PushBack(data2);
			SList<int32_t>::Iterator it;
			auto intExpression = [&it] { it++; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			it = intList.begin();
			Assert::AreNotEqual(*(it++), data2);
			Assert::AreEqual(*it, data2);

			SList<int32_t*> intPtrList;
			intPtrList.PushFront(&data);
			intPtrList.PushBack(&data2);
			SList<int32_t*>::Iterator it2;
			auto intPtrExpression = [&it2] { it2++; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			it2 = intPtrList.begin();
			Assert::AreNotEqual(*(it2++), &data2);
			Assert::AreEqual(*it2, &data2);

			SList<Foo> fooList;
			Foo foo(data), foo2(data2);
			fooList.PushFront(foo);
			fooList.PushBack(foo2);
			SList<Foo>::Iterator it3;
			auto fooExpression = [&it3] { it3++; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			it3 = fooList.begin();
			Assert::AreNotEqual(*(it3++), foo2);
			Assert::AreEqual(*it3, foo2);
		}

		TEST_METHOD(Iterator_Indirection_Operator)
		{
			int32_t data = 10, data2 = 20;

			// Non-const dereference
			SList<int32_t> intList;
			SList<int32_t>::Iterator it, it2;
			auto intExpression = [&it] { *it; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			it = intList.PushFront(data);
			it2 = intList.PushBack(data2);
			Assert::AreEqual(*it, data);
			Assert::AreEqual(*it2, data2);
			// Const dereference
			const SList<int32_t>::Iterator it3;
			auto intExpression2 = [&it3] { *it3; };
			Assert::ExpectException<std::runtime_error>(intExpression2);
			const SList<int32_t>::Iterator it4 = intList.begin();
			Assert::AreEqual(*it4, data);

			// Non-const dereference
			SList<int32_t*> intPtrList;
			SList<int32_t*>::Iterator it5, it6;
			auto intPtrExpression = [&it5] { *it5; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			it5 = intPtrList.PushFront(&data);
			it6 = intPtrList.PushBack(&data2);
			Assert::AreEqual(*it5, &data);
			Assert::AreEqual(*it6, &data2);
			// Const dereference
			const SList<int32_t*>::Iterator it7;
			auto intPtrExpression2 = [&it7] { *it7; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression2);
			const SList<int32_t*>::Iterator it8 = intPtrList.begin();
			Assert::AreEqual(*it8, &data);

			// Non-const dereference
			SList<Foo> fooList;
			Foo foo(data), foo2(data2);
			SList<Foo>::Iterator it9, it10;
			auto fooExpression = [&it9] { *it9; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			it9 = fooList.PushFront(foo);
			it10 = fooList.PushBack(foo2);
			Assert::AreEqual(*it9, foo);
			Assert::AreEqual(*it10, foo2);
			// Const dereference
			const SList<Foo>::Iterator it11;
			auto fooExpression2 = [&it11] { *it11; };
			Assert::ExpectException<std::runtime_error>(fooExpression2);
			const SList<Foo>::Iterator it12 = fooList.begin();
			Assert::AreEqual(*it12, foo);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListIteratorTest::sStartMemState;
}