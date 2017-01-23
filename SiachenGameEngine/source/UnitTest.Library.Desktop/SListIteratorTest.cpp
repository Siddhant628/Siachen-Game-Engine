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
			SList<int32_t>::Iterator It, It2;
			Assert::AreEqual(It, It2);
			auto intExpression = [&It] { It++; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			auto intExpression2 = [&It2] { ++It2; };
			Assert::ExpectException<std::runtime_error>(intExpression2);
			auto intExpression3 = [&It2] { *It2; };
			Assert::ExpectException<std::runtime_error>(intExpression3);
			// Copy constructor
			SList<int32_t> intList;
			intList.PushBack(data2);
			intList.PushFront(data);
			It = intList.Begin();
			SList<int32_t>::Iterator It3(It);
			Assert::AreEqual(It, It3);
			Assert::AreEqual(*It3, data);
			Assert::AreNotEqual(It, It2);

			// Default constructor
			SList<int32_t*>::Iterator It4, It5;
			Assert::AreEqual(It4, It5);
			auto intPrtExpression = [&It4] { It4++; };
			Assert::ExpectException<std::runtime_error>(intPrtExpression);
			auto intPrtExpression2 = [&It5] { ++It5; };
			Assert::ExpectException<std::runtime_error>(intPrtExpression2);
			auto intPrtExpression3 = [&It5] { *It5; };
			Assert::ExpectException<std::runtime_error>(intPrtExpression3);
			// Copy constructor
			SList<int32_t*> intPtrList;
			intPtrList.PushBack(&data2);
			intPtrList.PushFront(&data);
			SList<int32_t*>::Iterator It6 = intPtrList.Begin();
			SList<int32_t*>::Iterator It7(It6);
			Assert::AreEqual(It6, It7);
			Assert::AreEqual(*It7, &data);

			// Default constructor
			SList<int32_t>::Iterator It8, It9;
			Assert::AreEqual(It8, It9);
			auto fooExpression = [&It8] { It8++; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			auto fooExpression2 = [&It9] { ++It9; };
			Assert::ExpectException<std::runtime_error>(fooExpression2);
			auto fooExpression3 = [&It9] { *It9; };
			Assert::ExpectException<std::runtime_error>(fooExpression3);
			// Copy constructor
			Foo foo(data), foo2(data2);
			SList<Foo> fooList;
			fooList.PushBack(foo2);
			fooList.PushFront(foo);
			SList<Foo>::Iterator It10 = fooList.Begin();
			SList<Foo>::Iterator It11(It10);
			Assert::AreEqual(It10, It11);
			Assert::AreEqual(*It11, foo);

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListIteratorTest::sStartMemState;
}