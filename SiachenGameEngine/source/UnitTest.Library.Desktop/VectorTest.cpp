#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<Foo>(const Foo& foo)
			{
				std::wstringstream bufferStream;
				bufferStream << "Foo_" << foo.GetValue();
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<Vector<std::int32_t>::Iterator>(typename const Vector<std::int32_t>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					std::int32_t value = *it;
					bufferStream << "Vector_Integer_Iterator_" << value;
				}
				catch (std::exception){}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<Vector<std::int32_t*>::Iterator>(typename const Vector<std::int32_t*>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					std::int32_t* value = *it;
					bufferStream << "Vector_Integer*_Iterator_" << value;
				}
				catch (std::exception) {}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<Vector<Foo>::Iterator>(typename const Vector<Foo>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					Foo value = *it;
					bufferStream << "Vector_Foo_Iterator_" << value.GetValue();
				}
				catch (std::exception) {}
				return bufferStream.str();
			}
		}
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
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

		TEST_METHOD(Vector_Copy_Constructor)
		{
			std::int32_t data = 10, data2 = 20;

			Vector<std::int32_t> intVector;
			intVector.PushBack(data);
			intVector.PushBack(data2);

			Vector<std::int32_t> intVector2(intVector);
			Assert::AreEqual(intVector2.Front(), data);
			Assert::AreEqual(intVector2.Back(), data2);
			Assert::AreEqual(intVector.Size(), intVector2.Size());

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);

			Vector<std::int32_t*> intPtrVector2(intPtrVector);
			Assert::AreEqual(intPtrVector2.Front(), &data);
			Assert::AreEqual(intPtrVector2.Back(), &data2);
			Assert::AreEqual(intPtrVector.Size(), intPtrVector2.Size());

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2);

			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);
			Assert::AreEqual(fooVector.Front(), foo);
			Assert::AreEqual(fooVector.Back(), foo2);

			Vector<Foo> fooVector2(fooVector);
			Assert::AreEqual(fooVector2.Front(), foo);
			Assert::AreEqual(fooVector2.Back(), foo2);
			Assert::AreEqual(fooVector.Size(), fooVector2.Size());
		}

		TEST_METHOD(Vector_IsEmpty)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			Assert::IsTrue(intVector.IsEmpty());

			intVector.PushBack(data);
			Assert::IsFalse(intVector.IsEmpty());
			intVector.PopBack();
			Assert::IsTrue(intVector.IsEmpty());

			Vector<std::int32_t*> intPtrVector;
			Assert::IsTrue(intPtrVector.IsEmpty());

			intPtrVector.PushBack(&data);
			Assert::IsFalse(intPtrVector.IsEmpty());
			intPtrVector.PopBack();
			Assert::IsTrue(intPtrVector.IsEmpty());

			Vector<Foo> fooVector;
			Foo foo(data);
			Assert::IsTrue(fooVector.IsEmpty());

			fooVector.PushBack(foo);
			Assert::IsFalse(fooVector.IsEmpty());
			fooVector.PopBack();
			Assert::IsTrue(fooVector.IsEmpty());
		}

		TEST_METHOD(Vector_Front)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			// Empty vector
			auto intExpression = [&intVector] {intVector.Front(); };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// Non-empty vector
			intVector.PushBack(data);
			Assert::AreEqual(intVector.Front(), data);
			// Const version
			const Vector<std::int32_t> constIntVector(intVector);
			Assert::AreEqual(constIntVector.Front(), data);
			const Vector<std::int32_t> constIntVector2;
			auto constIntExpression = [&constIntVector2] {constIntVector2.Front(); };
			Assert::ExpectException<std::runtime_error>(constIntExpression);

			Vector<std::int32_t*> intPtrVector;
			// Empty vector
			auto intPtrExpression = [&intPtrVector] {intPtrVector.Front(); };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// Non-empty vector
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.Front(), &data);
			// Const version
			const Vector<std::int32_t*> constIntPtrVector(intPtrVector);
			Assert::AreEqual(constIntPtrVector.Front(), &data);
			const Vector<std::int32_t*> constIntPtrVector2;
			auto constIntPtrExpression = [&constIntPtrVector2] {constIntPtrVector2.Front(); };
			Assert::ExpectException<std::runtime_error>(constIntPtrExpression);

			Vector<Foo> fooVector;
			Foo foo(data);
			// Empty vector
			auto fooExpression = [&fooVector] {fooVector.Front(); };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// Non-empty vector
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.Front(), foo);
			// Const version
			const Vector<Foo> constFooVector(fooVector);
			Assert::AreEqual(constFooVector.Front(), foo);
			const Vector<Foo> constFooVector2;
			auto constFooExpression = [&constFooVector2] {constFooVector2.Front(); };
			Assert::ExpectException<std::runtime_error>(constFooExpression);
		}

		TEST_METHOD(Vector_Back)
		{
			std::int32_t data = 10, data2 = 20;

			Vector<std::int32_t> intVector;
			// Empty vector
			auto intExpression = [&intVector] {intVector.Back(); };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// Non-empty vector
			intVector.PushBack(data);
			Assert::AreEqual(intVector.Back(), data);
			intVector.PushBack(data2);
			Assert::AreEqual(intVector.Back(), data2);
			// Const version
			const Vector<std::int32_t> constIntVector(intVector);
			Assert::AreEqual(constIntVector.Back(), data2);
			const Vector<std::int32_t> constIntVector2;
			auto constIntExpression = [&constIntVector2] {constIntVector2.Back(); };
			Assert::ExpectException<std::runtime_error>(constIntExpression);

			Vector<std::int32_t*> intPtrVector;
			// Empty vector
			auto intPtrExpression = [&intPtrVector] {intPtrVector.Back(); };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// Non-empty vector
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.Back(), &data);
			intPtrVector.PushBack(&data2);
			Assert::AreEqual(intPtrVector.Back(), &data2);
			// Const version
			const Vector<std::int32_t*> constIntPtrVector(intPtrVector);
			Assert::AreEqual(constIntPtrVector.Back(), &data2);
			const Vector<std::int32_t*> constIntPtrVector2;
			auto constIntPtrExpression = [&constIntPtrVector2] {constIntPtrVector2.Back(); };
			Assert::ExpectException<std::runtime_error>(constIntPtrExpression);

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2);
			// Empty vector
			auto fooExpression = [&fooVector] {fooVector.Back(); };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// Non-empty vector
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.Back(), foo);
			fooVector.PushBack(foo2);
			Assert::AreEqual(fooVector.Back(), foo2);
			// Const version
			const Vector<Foo> constFooVector(fooVector);
			Assert::AreEqual(constFooVector.Back(), foo2);
			const Vector<Foo> constFooVector2;
			auto constFooExpression = [&constFooVector2] {constFooVector2.Back(); };
			Assert::ExpectException<std::runtime_error>(constFooExpression);
		}

		TEST_METHOD(Vector_Size)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			Assert::AreEqual(intVector.Size(), static_cast<std::uint32_t>(0));
			intVector.PushBack(data);
			Assert::AreEqual(intVector.Size(), static_cast<std::uint32_t>(1));
			intVector.PopBack();
			Assert::AreEqual(intVector.Size(), static_cast<std::uint32_t>(0));

			Vector<std::int32_t*> intPtrVector;
			Assert::AreEqual(intPtrVector.Size(), static_cast<std::uint32_t>(0));
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.Size(), static_cast<std::uint32_t>(1));
			intPtrVector.PopBack();
			Assert::AreEqual(intPtrVector.Size(), static_cast<std::uint32_t>(0));

			Vector<Foo> fooVector;
			Foo foo(data);
			Assert::AreEqual(fooVector.Size(), static_cast<std::uint32_t>(0));
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.Size(), static_cast<std::uint32_t>(1));
			fooVector.PopBack();
			Assert::AreEqual(fooVector.Size(), static_cast<std::uint32_t>(0));
		}

		TEST_METHOD(Vector_Capacity)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			Assert::AreEqual(intVector.Capacity(), static_cast<std::uint32_t>(0));
			intVector.PushBack(data);
			Assert::AreEqual(intVector.Capacity(), static_cast<std::uint32_t>(1));
			intVector.PopBack();
			Assert::AreEqual(intVector.Capacity(), static_cast<std::uint32_t>(1));
			intVector.PushBack(data);
			intVector.PushBack(data);
			intVector.PushBack(data);
			Assert::AreEqual(intVector.Capacity(), static_cast<std::uint32_t>(4));

			Vector<std::int32_t*> intPtrVector;
			Assert::AreEqual(intPtrVector.Capacity(), static_cast<std::uint32_t>(0));
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.Capacity(), static_cast<std::uint32_t>(1));
			intPtrVector.PopBack();
			Assert::AreEqual(intPtrVector.Capacity(), static_cast<std::uint32_t>(1));
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.Capacity(), static_cast<std::uint32_t>(4));

			Vector<Foo> fooVector;
			Foo foo(data);
			Assert::AreEqual(fooVector.Capacity(), static_cast<std::uint32_t>(0));
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.Capacity(), static_cast<std::uint32_t>(1));
			fooVector.PopBack();
			Assert::AreEqual(fooVector.Capacity(), static_cast<std::uint32_t>(1));
			fooVector.PushBack(foo);
			fooVector.PushBack(foo);
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.Capacity(), static_cast<std::uint32_t>(4));
		}

		TEST_METHOD(Vector_PushBack)
		{
			std::int32_t data = 10, data2 = 20, data3 = 30, data4 = 40;

			Vector<std::int32_t> intVector;
			intVector.PushBack(data);
			intVector.PushBack(data2);
			intVector.PushBack(data3);
			intVector.PushBack(data4);
			Assert::AreEqual(data4, intVector.Back());
			Assert::AreEqual(intVector.Size(), static_cast<std::uint32_t>(4));

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);
			intPtrVector.PushBack(&data3);
			intPtrVector.PushBack(&data4);
			Assert::AreEqual(&data4, intPtrVector.Back());
			Assert::AreEqual(intPtrVector.Size(), static_cast<std::uint32_t>(4));

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2), foo3(data3), foo4(data4);
			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);
			fooVector.PushBack(foo3);
			fooVector.PushBack(foo4);
			Assert::AreEqual(foo4, fooVector.Back());
			Assert::AreEqual(fooVector.Size(), static_cast<std::uint32_t>(4));
		}

		TEST_METHOD(Vector_PopBack)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			intVector.PopBack();
			intVector.PushBack(data);
			intVector.PopBack();

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.PopBack();
			intPtrVector.PushBack(&data);
			intPtrVector.PopBack();

			Vector<Foo> fooVector;
			Foo foo(data);
			fooVector.PopBack();
			fooVector.PushBack(foo);
			fooVector.PopBack();
		}

		TEST_METHOD(Vector_At)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			// Invalid index
			auto intExpression = [&intVector] { intVector.At(static_cast<std::uint32_t>(0)); };
			Assert::ExpectException<std::out_of_range>(intExpression);
			// Valid index
			intVector.PushBack(data);
			Assert::AreEqual(data, intVector.At(static_cast<std::uint32_t>(0)));

			Vector<std::int32_t*> intPtrVector;
			// Invalid index
			auto intPtrExpression = [&intPtrVector] { intPtrVector.At(static_cast<std::uint32_t>(0)); };
			Assert::ExpectException<std::out_of_range>(intPtrExpression);
			// Valid index
			intPtrVector.PushBack(&data);
			Assert::AreEqual(&data, intPtrVector.At(static_cast<std::uint32_t>(0)));

			Vector<Foo> fooVector;
			Foo foo(data);
			// Invalid index
			auto fooExpression = [&fooVector] { fooVector.At(static_cast<std::uint32_t>(0)); };
			Assert::ExpectException<std::out_of_range>(fooExpression);
			// Valid index
			fooVector.PushBack(foo);
			Assert::AreEqual(foo, fooVector.At(static_cast<std::uint32_t>(0)));
		}

		TEST_METHOD(Vector_Reserve)
		{
			std::uint32_t data = 10;
			std::int32_t data2 = 20;

			Vector<std::int32_t> intVector;
			// Initial reserve
			intVector.Reserve(static_cast<std::uint32_t>(0));
			intVector.PushBack(data);
			// Reserving less than the size
			auto intExpression = [&intVector] { intVector.Reserve(static_cast<std::uint32_t>(0)); };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// A general reserve
			intVector.Reserve(data);
			Assert::AreEqual(intVector.Capacity(), data);

			Vector<std::int32_t*> intPtrVector;
			// Initial reserve
			intPtrVector.Reserve(static_cast<std::uint32_t>(0));
			intPtrVector.PushBack(&data2);
			// Reserving less than the size
			auto intPtrExpression = [&intPtrVector] { intPtrVector.Reserve(static_cast<std::uint32_t>(0)); };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// A general reserve
			intPtrVector.Reserve(data);
			Assert::AreEqual(intPtrVector.Capacity(), data);

			Vector<Foo> fooVector;
			Foo foo(data2);
			// Initial reserve
			fooVector.Reserve(static_cast<std::uint32_t>(0));
			fooVector.PushBack(foo);
			// Reserving less than the size
			auto fooExpression = [&fooVector] { fooVector.Reserve(static_cast<std::uint32_t>(0)); };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// A general reserve
			fooVector.Reserve(data);
			Assert::AreEqual(fooVector.Capacity(), data);
		}

		TEST_METHOD(Vector_Clear)
		{
			std::int32_t data = 10, data2 = 20;

			Vector<std::int32_t> intVector;
			intVector.PushBack(data);
			intVector.PushBack(data2);
			Assert::AreEqual(intVector.Size(), static_cast<std::uint32_t>(2));
			intVector.Clear();
			Assert::AreEqual(intVector.Size(), static_cast<std::uint32_t>(0));

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);
			Assert::AreEqual(intPtrVector.Size(), static_cast<std::uint32_t>(2));
			intPtrVector.Clear();
			Assert::AreEqual(intPtrVector.Size(), static_cast<std::uint32_t>(0));

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2);
			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);
			Assert::AreEqual(fooVector.Size(), static_cast<std::uint32_t>(2));
			fooVector.Clear();
			Assert::AreEqual(fooVector.Size(), static_cast<std::uint32_t>(0));
		}

		TEST_METHOD(Vector_ClearAndFree)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			intVector.ClearAndFree();
			intVector.PushBack(data);
			Assert::AreEqual(intVector.Capacity(), static_cast<std::uint32_t>(1));
			intVector.ClearAndFree();
			Assert::IsTrue(intVector.IsEmpty());
			Assert::AreEqual(intVector.Capacity(), static_cast<std::uint32_t>(0));

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.ClearAndFree();
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.Capacity(), static_cast<std::uint32_t>(1));
			intPtrVector.ClearAndFree();
			Assert::IsTrue(intPtrVector.IsEmpty());
			Assert::AreEqual(intPtrVector.Capacity(), static_cast<std::uint32_t>(0));

			Vector<Foo> fooVector;
			Foo foo(data);
			fooVector.ClearAndFree();
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.Capacity(), static_cast<std::uint32_t>(1));
			fooVector.ClearAndFree();
			Assert::IsTrue(fooVector.IsEmpty());
			Assert::AreEqual(fooVector.Capacity(), static_cast<std::uint32_t>(0));
		}

		TEST_METHOD(Vector_Begin)
		{
			Vector<std::int32_t> intVector, intVector2;
			Vector<std::int32_t>::Iterator it = intVector.begin();
			Vector<std::int32_t>::Iterator it2 = intVector.begin();
			Assert::AreEqual(it, it2);
			it2 = intVector2.begin();
			Assert::AreNotEqual(it, it2);
			Assert::AreEqual(intVector.begin(), intVector.end());

			Vector<std::int32_t*> intPtrVector, intPtrVector2;
			Vector<std::int32_t*>::Iterator it3 = intPtrVector.begin();
			Vector<std::int32_t*>::Iterator it4 = intPtrVector.begin();
			Assert::AreEqual(it3, it4);
			it4 = intPtrVector2.begin();
			Assert::AreNotEqual(it3, it4);
			Assert::AreEqual(intPtrVector.begin(), intPtrVector.end());

			Vector<Foo> fooVector, fooVector2;
			Vector<Foo>::Iterator it5 = fooVector.begin();
			Vector<Foo>::Iterator it6 = fooVector.begin();
			Assert::AreEqual(it5, it6);
			it6 = fooVector2.begin();
			Assert::AreNotEqual(it5, it6);
			Assert::AreEqual(fooVector.begin(), fooVector.end());
		}

		TEST_METHOD(Vector_End)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector, intVector2;
			Assert::AreEqual(intVector.begin(), intVector.end());
			intVector.PushBack(data);
			intVector2.PushBack(data);
			Assert::AreNotEqual(intVector.begin(), intVector.end());
			Vector<std::int32_t>::Iterator it = intVector.end();
			Vector<std::int32_t>::Iterator it2 = intVector.end();
			Assert::AreEqual(it, it2);
			it2 = intVector2.end();
			Assert::AreNotEqual(it, it2);

			Vector<std::int32_t*> intPtrVector, intPtrVector2;
			Assert::AreEqual(intPtrVector.begin(), intPtrVector.end());
			intPtrVector.PushBack(&data);
			intPtrVector2.PushBack(&data);
			Assert::AreNotEqual(intPtrVector.begin(), intPtrVector.end());
			Vector<std::int32_t*>::Iterator it3 = intPtrVector.end();
			Vector<std::int32_t*>::Iterator it4 = intPtrVector.end();
			Assert::AreEqual(it3, it4);
			it4 = intPtrVector2.end();
			Assert::AreNotEqual(it3, it4);

			Vector<Foo> fooVector, fooVector2;
			Foo foo(data);
			Assert::AreEqual(fooVector.begin(), fooVector.end());
			fooVector.PushBack(foo);
			fooVector2.PushBack(foo);
			Assert::AreNotEqual(fooVector.begin(), fooVector.end());
			Vector<Foo>::Iterator it5 = fooVector.end();
			Vector<Foo>::Iterator it6 = fooVector.end();
			Assert::AreEqual(it5, it6);
			it6 = fooVector2.end();
			Assert::AreNotEqual(it5, it6);
			
		}

		TEST_METHOD(Vector_Find)
		{
			std::int32_t data = 10, data2 = 20, data3 = 30;
			
			Vector<std::int32_t> intVector;
			intVector.PushBack(data);
			intVector.PushBack(data2);
			Vector<std::int32_t>::Iterator it = intVector.Find(data3);
			Assert::AreEqual(it, intVector.end());
			it = intVector.Find(data);
			Assert::AreEqual(it, intVector.begin());
			Assert::AreEqual(++it, intVector.Find(data2));

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);
			Vector<std::int32_t*>::Iterator it2 = intPtrVector.Find(&data3);
			Assert::AreEqual(it2, intPtrVector.end());
			it2 = intPtrVector.Find(&data);
			Assert::AreEqual(it2, intPtrVector.begin());
			Assert::AreEqual(++it2, intPtrVector.Find(&data2));

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2), foo3(data3);
			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);
			Vector<Foo>::Iterator it3 = fooVector.Find(foo3);
			Assert::AreEqual(it3, fooVector.end());
			it3 = fooVector.Find(foo);
			Assert::AreEqual(it3, fooVector.begin());
			Assert::AreEqual(++it3, fooVector.Find(foo2));
		}

		TEST_METHOD(Vector_Remove_Iterators)
		{

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}