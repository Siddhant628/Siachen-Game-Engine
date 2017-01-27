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

			Vector<int> intVector;
			intVector.PushBack(data);
			intVector.PushBack(data2);

			Vector<int> intVector2(intVector);
			Assert::AreEqual(intVector2.Front(), data);
			Assert::AreEqual(intVector2.Back(), data2);
			Assert::AreEqual(intVector.Size(), intVector2.Size());

			Vector<int*> intPtrVector;
			intPtrVector.PushBack(&data);
			intPtrVector.PushBack(&data2);

			Vector<int*> intPtrVector2(intPtrVector);
			Assert::AreEqual(intPtrVector2.Front(), &data);
			Assert::AreEqual(intPtrVector2.Back(), &data2);
			Assert::AreEqual(intPtrVector.Size(), intPtrVector2.Size());

			Vector<Foo> fooVector;
			Foo foo(data), foo2(data2);
			fooVector.PushBack(foo);
			fooVector.PushBack(foo2);

			Vector<Foo> fooVector2(fooVector);
			Assert::AreEqual(fooVector2.Front(), foo);
			Assert::AreEqual(fooVector2.Back(), foo2);
			Assert::AreEqual(fooVector.Size(), fooVector2.Size());

		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}