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
			// To string method for comparing Foos
			template<>
			std::wstring ToString<Foo>(const Foo& foo)
			{
				std::wstringstream bufferStream;
				bufferStream << "Foo_" << foo.GetValue();
				return bufferStream.str();
			}
			// To string method for comparing vector<int> iterators 
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
			// To string method for comparing vector<int*> iterators 
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
			// To string method for comparing vector<Foo> iterators 
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

		TEST_METHOD(Vector_FixedSize_Constructor)
		{
			std::uint32_t initialSize = 10;

			Vector<std::int32_t> intVector(initialSize);
			Assert::AreEqual(initialSize, intVector.Size());
			Assert::AreEqual(initialSize, intVector.Capacity());
			Assert::AreEqual(int32_t(), intVector.Front());
			Assert::AreEqual(int32_t(), intVector.Back());

			Vector<std::int32_t*> intPtrVector(initialSize);
			Assert::AreEqual(initialSize, intPtrVector.Size());
			Assert::AreEqual(initialSize, intPtrVector.Capacity());

			Vector<Foo> fooVector(initialSize);
			Assert::AreEqual(initialSize, fooVector.Size());
			Assert::AreEqual(initialSize, fooVector.Capacity());
			Assert::AreEqual(Foo(), fooVector.Front());
			Assert::AreEqual(Foo(), fooVector.Back());
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
			intVector.Reserve(static_cast<std::uint32_t>(0), false);
			intVector.PushBack(data);
			// Reserving less than the size
			auto intExpression = [&intVector] { intVector.Reserve(static_cast<std::uint32_t>(0), false); };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// A general reserve
			intVector.Reserve(data, false);
			Assert::AreEqual(intVector.Capacity(), data);

			Vector<std::int32_t*> intPtrVector;
			// Initial reserve
			intPtrVector.Reserve(static_cast<std::uint32_t>(0), false);
			intPtrVector.PushBack(&data2);
			// Reserving less than the size
			auto intPtrExpression = [&intPtrVector] { intPtrVector.Reserve(static_cast<std::uint32_t>(0), false); };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// A general reserve
			intPtrVector.Reserve(data, false);
			Assert::AreEqual(intPtrVector.Capacity(), data);

			Vector<Foo> fooVector;
			Foo foo(data2);
			// Initial reserve
			fooVector.Reserve(static_cast<std::uint32_t>(0), false);
			fooVector.PushBack(foo);
			// Reserving less than the size
			auto fooExpression = [&fooVector] { fooVector.Reserve(static_cast<std::uint32_t>(0), false); };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// A general reserve
			fooVector.Reserve(data, false);
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
			std::int32_t data = 10, data2 = 20, data3 = 30;
			
			Vector<std::int32_t> intVector, intVector2;
			Vector<std::int32_t>::Iterator otherIt = intVector2.end();
			Vector<std::int32_t>::Iterator it = intVector.PushBack(data);
			Vector<std::int32_t>::Iterator it2 = intVector.PushBack(data2);
			Vector<std::int32_t>::Iterator it3 = intVector.PushBack(data3);
			// In case the iterators are invalid
			auto intExpression = [&intVector, &otherIt, &it] {intVector.Remove(otherIt, it); };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// In case the iterator order or size index is invalid
			auto intExpression2 = [&intVector, &it2, &it] {intVector.Remove(it2, it); };
			Assert::ExpectException<std::out_of_range>(intExpression2);
			// In case of valid removal
			Assert::IsTrue(intVector.Remove(it, it3));
			Assert::AreEqual(data3, intVector.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(1), intVector.Size());

			Vector<std::int32_t*> intPtrVector, intPtrVector2;
			Vector<std::int32_t*>::Iterator otherIt2 = intPtrVector2.end();
			Vector<std::int32_t*>::Iterator it4 = intPtrVector.PushBack(&data);
			Vector<std::int32_t*>::Iterator it5 = intPtrVector.PushBack(&data2);
			Vector<std::int32_t*>::Iterator it6 = intPtrVector.PushBack(&data3);
			// In case the iterators are invalid
			auto intPtrExpression = [&intPtrVector, &otherIt2, &it4] {intPtrVector.Remove(otherIt2, it4); };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// In case the iterator order or size index is invalid
			auto intPtrExpression2 = [&intPtrVector, &it5, &it4] {intPtrVector.Remove(it5, it4); };
			Assert::ExpectException<std::out_of_range>(intPtrExpression2);
			// In case of valid removal
			Assert::IsTrue(intPtrVector.Remove(it4, it6));
			Assert::AreEqual(&data3, intPtrVector.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(1), intPtrVector.Size());

			Vector<Foo> fooVector, fooVector2;
			Foo foo(data), foo2(data2), foo3(data3);
			Vector<Foo>::Iterator otherIt3 = fooVector2.end();
			Vector<Foo>::Iterator it7 = fooVector.PushBack(foo);
			Vector<Foo>::Iterator it8 = fooVector.PushBack(foo2);
			Vector<Foo>::Iterator it9 = fooVector.PushBack(foo3);
			// In case the iterators are invalid
			auto fooExpression = [&fooVector, &otherIt3, &it7] {fooVector.Remove(otherIt3, it7); };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// In case the iterator order or size index is invalid
			auto fooExpression2 = [&fooVector, &it8, &it7] {fooVector.Remove(it8, it7); };
			Assert::ExpectException<std::out_of_range>(fooExpression2);
			// In case of valid removal
			Assert::IsTrue(fooVector.Remove(it7, it9));
			Assert::AreEqual(foo3, fooVector.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(1), fooVector.Size());
		}

		TEST_METHOD(Vector_Remove_Item)
		{
			std::int32_t data = 10, data2 = 20;

			Vector<std::int32_t> intVector;
			Assert::IsFalse(intVector.Remove(data));
			intVector.PushBack(data);
			Assert::IsFalse(intVector.Remove(data2));
			intVector.PushBack(data2);
			Assert::AreEqual(intVector.Back(), data2);
			Assert::IsTrue(intVector.Remove(data2));
			Assert::AreEqual(intVector.Back(), data);
			intVector.PushBack(data2);
			Assert::IsTrue(intVector.Remove(data));

			Vector<std::int32_t*> intPtrVector;
			Assert::IsFalse(intPtrVector.Remove(&data));
			intPtrVector.PushBack(&data);
			Assert::IsFalse(intPtrVector.Remove(&data2));
			intPtrVector.PushBack(&data2);
			Assert::AreEqual(intPtrVector.Back(), &data2);
			Assert::IsTrue(intPtrVector.Remove(&data2));
			Assert::AreEqual(intPtrVector.Back(), &data);
			intPtrVector.PushBack(&data2);
			Assert::IsTrue(intPtrVector.Remove(&data));

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2);
			Assert::IsFalse(fooVector.Remove(foo));
			fooVector.PushBack(foo);
			Assert::IsFalse(fooVector.Remove(foo2));
			fooVector.PushBack(foo2);
			Assert::AreEqual(fooVector.Back(), foo2);
			Assert::IsTrue(fooVector.Remove(foo2));
			Assert::AreEqual(fooVector.Back(), foo);
			fooVector.PushBack(foo2);
			Assert::IsTrue(fooVector.Remove(foo));
		}

		TEST_METHOD(Vector_Assignment_Operator)
		{
			std::int32_t data = 10, data2 = 20, data3;

			Vector<std::int32_t> intVector, intVector2;
			intVector.PushBack(data);
			intVector.PushBack(data2);
			intVector.PushBack(data3);
			intVector2.PushBack(data2);
			intVector2.PushBack(data);
			Assert::AreNotEqual(intVector.Front(), intVector2.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(2), intVector2.Size());
			intVector2 = intVector;
			Assert::AreEqual(intVector.Front(), intVector2.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(3), intVector2.Size());

			Vector<std::int32_t*> intPtrVector, intPtrVector2;
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);
			intPtrVector.PushBack(&data3);
			intPtrVector2.PushBack(&data2);
			intPtrVector2.PushBack(&data);
			Assert::AreNotEqual(intPtrVector.Front(), intPtrVector2.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(2), intPtrVector2.Size());
			intPtrVector2 = intPtrVector;
			Assert::AreEqual(intPtrVector.Front(), intPtrVector2.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(3), intPtrVector2.Size());

			Vector<Foo> fooVector, fooVector2;
			Foo foo(data), foo2(data2), foo3(data3);
			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);
			fooVector.PushBack(foo3);
			fooVector2.PushBack(foo2);
			fooVector2.PushBack(foo);
			Assert::AreNotEqual(fooVector.Front(), fooVector2.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(2), fooVector2.Size());
			fooVector2 = fooVector;
			Assert::AreEqual(fooVector.Front(), fooVector2.Front());
			Assert::AreEqual(static_cast<std::uint32_t>(3), fooVector2.Size());
		}

		TEST_METHOD(Vector_Subscript_Operator)
		{
			std::int32_t data = 10, data2 = 20;

			Vector<std::int32_t> intVector;
			const Vector<std::int32_t> intVectorEmpty(intVector);
			// When index is invalid
			auto intExpression1 = [&intVector] { intVector[0]; };
			Assert::ExpectException<std::out_of_range>(intExpression1);
			// When index is valid
			intVector.PushBack(data);
			intVector.PushBack(data2);
			Assert::AreEqual(intVector[0], data);
			Assert::AreEqual(intVector[1], data2);
			// In case of const vector
			const Vector<std::int32_t> intVector2(intVector);
			Assert::AreEqual(intVector2[0], data);
			Assert::AreEqual(intVector2[1], data2);
			auto intExpression2 = [&intVectorEmpty] { intVectorEmpty[0]; };
			Assert::ExpectException<std::out_of_range>(intExpression2);

			Vector<std::int32_t*> intPtrVector;
			const Vector<std::int32_t*> intPtrVectorEmpty(intPtrVector);
			// When index is invalid
			auto intPtrExpression = [&intPtrVector] { intPtrVector[0]; };
			Assert::ExpectException<std::out_of_range>(intPtrExpression);
			// When index is valid
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);
			Assert::AreEqual(intPtrVector[0], &data);
			Assert::AreEqual(intPtrVector[1], &data2);
			// In case of const vector
			const Vector<std::int32_t*> intPtrVector2(intPtrVector);
			Assert::AreEqual(intPtrVector2[0], &data);
			Assert::AreEqual(intPtrVector2[1], &data2);
			auto intPtrExpression2 = [&intPtrVectorEmpty] { intPtrVectorEmpty[0]; };
			Assert::ExpectException<std::out_of_range>(intPtrExpression2);

			Foo foo(data), foo2(data2);
			Vector<Foo> fooVector;
			const Vector<Foo> fooVectorEmpty(fooVector);
			// When index is invalid
			auto fooExpression1 = [&fooVector] { fooVector[0]; };
			Assert::ExpectException<std::out_of_range>(fooExpression1);
			// When index is valid
			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);
			Assert::AreEqual(fooVector[0], foo);
			Assert::AreEqual(fooVector[1], foo2);
			// In case of const vector
			const Vector<Foo> fooVector2(fooVector);
			Assert::AreEqual(fooVector2[0], foo);
			Assert::AreEqual(fooVector2[1], foo2);
			auto fooExpression2 = [&fooVectorEmpty] { fooVectorEmpty[0]; };
			Assert::ExpectException<std::out_of_range>(fooExpression2);
		}

		TEST_METHOD(Iterator_Constructors)
		{
			// Default constructor
			Vector<std::int32_t> intVector;
			Vector<std::int32_t>::Iterator intIt, intIt2;
			Assert::AreEqual(intIt, intIt2);
			// Copy constructor
			intIt = intVector.begin();
			Assert::AreNotEqual(intIt, intIt2);
			Vector<std::int32_t>::Iterator intIt3(intIt);
			Assert::AreEqual(intIt, intIt3);

			// Default constructor
			Vector<std::int32_t*> intPtrVector;
			Vector<std::int32_t*>::Iterator intPtrIt, intPtrIt2;
			Assert::AreEqual(intPtrIt, intPtrIt2);
			// Copy constructor
			intPtrIt = intPtrVector.begin();
			Assert::AreNotEqual(intPtrIt, intPtrIt2);
			Vector<std::int32_t*>::Iterator intPtrIt3(intPtrIt);
			Assert::AreEqual(intPtrIt, intPtrIt3);

			// Default constructor
			Vector<Foo> fooVector;
			Vector<Foo>::Iterator fooIt, fooIt2;
			Assert::AreEqual(fooIt, fooIt2);
			// Copy constructor
			fooIt = fooVector.begin();
			Assert::AreNotEqual(fooIt, fooIt2);
			Vector<Foo>::Iterator fooIt3(fooIt);
			Assert::AreEqual(fooIt, fooIt3);
		}

		TEST_METHOD(Iterator_Assignment_Operator)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			intVector.PushBack(data);
			Vector<std::int32_t>::Iterator it = intVector.begin();
			Vector<std::int32_t>::Iterator it2 = intVector.end();
			Assert::AreNotEqual(it, it2);
			it = it2;
			Assert::AreEqual(it, it2);

			Vector<std::int32_t*> intPtrVector;
			intPtrVector.PushBack(&data);
			Vector<std::int32_t*>::Iterator it3 = intPtrVector.begin();
			Vector<std::int32_t*>::Iterator it4 = intPtrVector.end();
			Assert::AreNotEqual(it3, it4);
			it3 = it4;
			Assert::AreEqual(it3, it4);

			Vector<Foo> fooVector;
			Foo foo(data);
			fooVector.PushBack(foo);
			Vector<Foo>::Iterator it5 = fooVector.begin();
			Vector<Foo>::Iterator it6 = fooVector.end();
			Assert::AreNotEqual(it5, it6);
			it5 = it6;
			Assert::AreEqual(it5, it6);
		}

		TEST_METHOD(Iterator_Equals_Operator)
		{
			Vector<std::int32_t>::Iterator it, it2;
			Assert::IsTrue(it == it2);

			Vector<std::int32_t*>::Iterator it3, it4;
			Assert::IsTrue(it3 == it4);

			Vector<Foo>::Iterator it5, it6;
			Assert::IsTrue(it5 == it6);
		}

		TEST_METHOD(Iterator_Inequals_Operator)
		{
			std::int32_t data = 10, data2 = 20;

			Vector<std::int32_t> intVector;
			Vector<std::int32_t>::Iterator it = intVector.PushBack(data);
			Vector<std::int32_t>::Iterator it2 = intVector.PushBack(data2);
			Assert::IsTrue(it++ != it2);
			Assert::IsFalse(it != it2);

			Vector<std::int32_t*> intPtrVector;
			Vector<std::int32_t*>::Iterator it3 = intPtrVector.PushBack(&data);
			Vector<std::int32_t*>::Iterator it4 = intPtrVector.PushBack(&data2);
			Assert::IsTrue(it3++ != it4);
			Assert::IsFalse(it3 != it4);

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2);
			Vector<Foo>::Iterator it5 = fooVector.PushBack(foo);
			Vector<Foo>::Iterator it6 = fooVector.PushBack(foo2);
			Assert::IsTrue(it5++ != it6);
			Assert::IsFalse(it5 != it6);
		}

		TEST_METHOD(Iterator_PreIncrement_Operator)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			Vector<std::int32_t>::Iterator it;
			// In case the iterator isn't associated with any vector
			auto intExpression = [&it] { ++it; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// Invalid index
			it = intVector.begin();
			auto intExpression2 = [&it] { ++it; };
			Assert::ExpectException<std::runtime_error>(intExpression2);
			// Successful pre-increment
			intVector.PushBack(data);
			Assert::AreEqual(intVector.end(), ++it);

			Vector<std::int32_t*> intPtrVector;
			Vector<std::int32_t*>::Iterator it2;
			// In case the iterator isn't associated with any vector
			auto intPtrExpression = [&it2] { ++it2; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// Invalid index
			it2 = intPtrVector.begin();
			auto intPtrExpression2 = [&it2] { ++it2; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression2);
			// Successful pre-increment
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.end(), ++it2);

			Foo foo(data);
			Vector<Foo> fooVector;
			Vector<Foo>::Iterator it3;
			// In case the iterator isn't associated with any vector
			auto fooExpression = [&it3] { ++it3; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// Invalid index
			it3 = fooVector.begin();
			auto fooExpression2 = [&it3] { ++it3; };
			Assert::ExpectException<std::runtime_error>(fooExpression2);
			// Successful pre-increment
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.end(), ++it3);
		}

		TEST_METHOD(Iterator_PostIncrement_Operator)
		{
			std::int32_t data = 10;

			Vector<std::int32_t> intVector;
			Vector<std::int32_t>::Iterator it;
			// In case the iterator isn't associated with any vector
			auto intExpression = [&it] { it++; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			// Invalid index
			it = intVector.begin();
			auto intExpression2 = [&it] { it++; };
			Assert::ExpectException<std::runtime_error>(intExpression2);
			// Successful post-increment
			intVector.PushBack(data);
			Assert::AreEqual(intVector.begin(), it++);
			Assert::AreEqual(intVector.end(), it);

			Vector<std::int32_t*> intPtrVector;
			Vector<std::int32_t*>::Iterator it2;
			// In case the iterator isn't associated with any vector
			auto intPtrExpression = [&it2] { it2++; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			// Invalid index
			it2 = intPtrVector.begin();
			auto intPtrExpression2 = [&it2] { it2++; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression2);
			// Successful post-increment
			intPtrVector.PushBack(&data);
			Assert::AreEqual(intPtrVector.begin(), it2++);
			Assert::AreEqual(intPtrVector.end(), it2);

			Foo foo(data);
			Vector<Foo> fooVector;
			Vector<Foo>::Iterator it3;
			// In case the iterator isn't associated with any vector
			auto fooExpression = [&it3] { it3++; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			// Invalid index
			it3 = fooVector.begin();
			auto fooExpression2 = [&it3] { it3++; };
			Assert::ExpectException<std::runtime_error>(fooExpression2);
			// Successful post-increment
			fooVector.PushBack(foo);
			Assert::AreEqual(fooVector.begin(), it3++);
			Assert::AreEqual(fooVector.end(), it3);
		}

		TEST_METHOD(Iterator_Indirection_Operator)
		{
			int32_t data = 10;

			Vector<std::int32_t> intVector;
			Vector<std::int32_t>::Iterator it;
			const Vector<std::int32_t>::Iterator it2;
			// In case the iterator isn't associated with any vector
			auto intExpression = [&it] { *it; };
			Assert::ExpectException<std::runtime_error>(intExpression);
			auto constIntExpression = [&it2] { *it2; };
			Assert::ExpectException<std::runtime_error>(constIntExpression);
			// In case the iterator isn't associated with an item in the vector
			it = intVector.begin();
			auto intExpression2 = [&it] { *it; };
			Assert::ExpectException<std::out_of_range>(intExpression2);
			const Vector<std::int32_t>::Iterator it3(it);
			auto constIntExpression2 = [&it3] { *it3; };
			Assert::ExpectException<std::out_of_range>(constIntExpression2);
			// A valid dereference
			intVector.PushBack(data);
			it = intVector.begin();
			Assert::AreEqual(*it, data);
			const Vector<std::int32_t>::Iterator it4(it);
			Assert::AreEqual(*it4, data);

			Vector<std::int32_t*> intPtrVector;
			Vector<std::int32_t*>::Iterator intPtrIt;
			const Vector<std::int32_t*>::Iterator intPtrIt2;
			// In case the iterator isn't associated with any vector
			auto intPtrExpression = [&intPtrIt] { *intPtrIt; };
			Assert::ExpectException<std::runtime_error>(intPtrExpression);
			auto constIntPtrExpression = [&intPtrIt2] { *intPtrIt2; };
			Assert::ExpectException<std::runtime_error>(constIntPtrExpression);
			// In case the iterator isn't associated with an item in the vector
			intPtrIt = intPtrVector.begin();
			auto intPtrExpression2 = [&intPtrIt] { *intPtrIt; };
			Assert::ExpectException<std::out_of_range>(intPtrExpression2);
			const Vector<std::int32_t*>::Iterator intPtrIt3(intPtrIt);
			auto constIntPtrExpression2 = [&intPtrIt3] { *intPtrIt3; };
			Assert::ExpectException<std::out_of_range>(constIntPtrExpression2);
			// A valid dereference
			intPtrVector.PushBack(&data);
			intPtrIt = intPtrVector.begin();
			Assert::AreEqual(*intPtrIt, &data);
			const Vector<std::int32_t*>::Iterator itPtrIt4(intPtrIt);
			Assert::AreEqual(*itPtrIt4, &data);

			Foo foo(data);
			Vector<Foo> fooVector;
			Vector<Foo>::Iterator fooIt;
			const Vector<Foo>::Iterator fooIt2;
			// In case the iterator isn't associated with any vector
			auto fooExpression = [&fooIt] { *fooIt; };
			Assert::ExpectException<std::runtime_error>(fooExpression);
			auto constFooExpression = [&fooIt2] { *fooIt2; };
			Assert::ExpectException<std::runtime_error>(constFooExpression);
			// In case the iterator isn't associated with an item in the vector
			fooIt = fooVector.begin();
			auto fooExpression2 = [&fooIt] { *fooIt; };
			Assert::ExpectException<std::out_of_range>(fooExpression2);
			const Vector<Foo>::Iterator fooIt3(fooIt);
			auto constFooExpression2 = [&fooIt3] { *fooIt3; };
			Assert::ExpectException<std::out_of_range>(constFooExpression2);
			// A valid dereference
			fooVector.PushBack(foo);
			fooIt = fooVector.begin();
			Assert::AreEqual(*fooIt, foo);
			const Vector<Foo>::Iterator fooIt4(fooIt);
			Assert::AreEqual(*fooIt4, foo);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}