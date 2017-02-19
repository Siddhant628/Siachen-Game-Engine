#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::Containers;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeTest)
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

		TEST_METHOD(Scope_Append)
		{
			std::string stringData = "IntegerData";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Datum scopeDatum = scope.Append(stringData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(), intData);

			scope.Append(stringData).PushBack(intData2);
			scopeDatum = scope.Append(stringData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(), intData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(1U), intData2);
		}

		TEST_METHOD(Scope_AppendScope)
		{
			std::string stringData = "BabyScope", stringData2 = "IntegerData";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData2).PushBack(intData2);
			scope.AppendScope(stringData).Append(stringData).PushBack(intData);
			Assert::AreEqual(scope.Append(stringData).Get<Scope*>()->Append(stringData).Get<std::int32_t>(), intData);

			scope.AppendScope(stringData).Append(stringData).PushBack(intData2);
			Assert::AreEqual(scope.Append(stringData).Get<Scope*>(1)->Append(stringData).Get<std::int32_t>(), intData2);
		}

		TEST_METHOD(Scope_Find)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData2);
			Assert::IsNull(scope.Find(stringData2));

			scope.Append(stringData2).PushBack(intData);
			Assert::AreEqual(scope.Find(stringData2)->Get<std::int32_t>(), intData);
		}

		TEST_METHOD(Scope_Search)
		{
			std::string stringData = "IntegerData", stringData2 = "BabyScope", stringData3 = "IntegerData2";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData2);
			childScope->Append(stringData3).PushBack(intData2);

			Scope* searchResult;
			childScope->Search("Hello", nullptr);
			
			childScope->Search(stringData3, &searchResult);
			Assert::AreEqual((searchResult)->Append(stringData3).Get<std::int32_t>(), intData2);

			childScope->Search(stringData, &searchResult);
			Assert::AreEqual((searchResult)->Append(stringData).Get<std::int32_t>(), intData);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}