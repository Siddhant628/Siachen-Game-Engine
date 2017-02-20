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
			Assert::AreEqual(scope.Find(stringData)->Get<std::int32_t>(), intData2);
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
			Assert::IsNull(childScope->Search("Hello", &searchResult));
			
			childScope->Search(stringData3, &searchResult);
			Assert::AreEqual((searchResult)->Append(stringData3).Get<std::int32_t>(), intData2);

			childScope->Search(stringData, &searchResult);
			Assert::AreEqual((searchResult)->Append(stringData).Get<std::int32_t>(), intData);
		}

		TEST_METHOD(Scope_Orphan)
		{
			std::string stringData = "IntegerData", stringData2 = "BabyScope", stringData3 = "IntegerData2", stringData4 = "BabyScope2";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData2);
			
			childScope->Append(stringData3).PushBack(intData2);
			childScope->AppendScope(stringData4).Append(stringData).PushBack(intData);
			
			Assert::IsFalse(scope.Orphan());

			Assert::IsTrue(childScope->Orphan());
			Assert::IsNull(childScope->GetParent());

			delete childScope;

		}
	
		TEST_METHOD(Scope_Adopt)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "IntegerData3", stringData4 = "IntegerData4", stringData5 = "BabyScope", stringData6 = "BabyScope2";
			Scope scope, scope2;
			std::int32_t intData = 10, intData2 = 20, intData3 = 30, intData4 = 40;
			Scope* searchResult;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData5);
			childScope->Append(stringData2).PushBack(intData2);
			
			scope2.Append(stringData3).PushBack(intData3);
			Scope* childScope2 = &scope2.AppendScope(stringData6);
			childScope2->Append(stringData4).PushBack(intData4);

			Assert::IsNull(childScope2->Search(stringData, &searchResult));
			scope.Adopt(*childScope2, stringData4);
			Assert::IsNotNull(childScope2->Search(stringData, &searchResult));
			Assert::AreEqual(childScope2->Search(stringData, &searchResult)->Get<std::int32_t>(), intData);

		}

		TEST_METHOD(Scope_GetParent)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "IntegerData3", stringData4 = "IntegerData4", stringData5 = "BabyScope", stringData6 = "BabyScope2";
			Scope scope, scope2;
			std::int32_t intData = 10, intData2 = 20, intData3 = 30, intData4 = 40;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData5);
			childScope->Append(stringData2).PushBack(intData2);

			scope2.Append(stringData3).PushBack(intData3);
			Scope* childScope2 = &scope2.AppendScope(stringData6);
			childScope2->Append(stringData4).PushBack(intData4);

			Assert::IsTrue(*childScope->GetParent() == scope);
			Assert::IsTrue(*childScope2->GetParent() != scope);
			Assert::IsTrue(*childScope2->GetParent() == scope2);
			Assert::IsTrue(*childScope->GetParent() != scope2);

		}

		TEST_METHOD(Scope_Subscript_Operator_Append)
		{
			std::string stringData = "IntegerData";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope[stringData].PushBack(intData);
			Datum scopeDatum = scope["IntegerData"];
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(), intData);

			scope[stringData].PushBack(intData2);
			scopeDatum = scope["IntegerData"];
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(), intData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(1U), intData2);
		}

		TEST_METHOD(Scope_Subscript_Operator_Index)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20, intData3 = 30;

			scope.Append(stringData).PushBack(intData);
			Assert::AreEqual(scope[0].Get<std::int32_t>(), intData);

			scope.Append(stringData).PushBack(intData2);
			Assert::AreEqual(scope[0].Get<std::int32_t>(), intData);
			Assert::AreEqual(scope[0].Get<std::int32_t>(1), intData2);

			scope.Append(stringData2).PushBack(intData3);
			Assert::AreEqual(scope[1].Get<std::int32_t>(), intData3);

			//Const version

			const Scope scope2(scope);

			Assert::AreEqual(scope2[0].Get<std::int32_t>(), intData);
			Assert::AreEqual(scope2[0].Get<std::int32_t>(1), intData2);
			Assert::AreEqual(scope2[1].Get<std::int32_t>(), intData3);

		}

		TEST_METHOD(Scope_Equals_Operator)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "BabyScope";
			Scope scope, scope2;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData3);
			childScope->Append(stringData2).PushBack(intData2);

			Scope scope3(scope);

			Assert::IsFalse(scope == scope2);
			Assert::IsTrue(scope == scope3);
		
			scope2.Append(stringData).PushBack(intData);
			Scope* childScope2 = &scope2.AppendScope(stringData3);
			childScope2->Append(stringData2).PushBack(intData);

			Assert::IsFalse(scope == scope2);
		}

		TEST_METHOD(Scope_Inequals_Operator)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "BabyScope";
			Scope scope, scope2;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData3);
			childScope->Append(stringData2).PushBack(intData2);

			Scope scope3(scope);

			Assert::IsTrue(scope != scope2);
			Assert::IsFalse(scope != scope3);

			scope2.Append(stringData).PushBack(intData);
			Scope* childScope2 = &scope2.AppendScope(stringData3);
			childScope2->Append(stringData2).PushBack(intData);

			Assert::IsTrue(scope != scope2);
		}

		TEST_METHOD(Scope_Copy_Constructor)
		{

			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "BabyScope";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData3);
			childScope->Append(stringData2).PushBack(intData2);

			Scope scope2(scope);

			Assert::IsTrue(scope == scope2);
		}

		TEST_METHOD(Scope_Assignment_Operator)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "IntegerData3", stringData4 = "IntegerData4", stringData5 = "BabyScope", stringData6 = "BabyScope2";
			Scope scope, scope2;
			std::int32_t intData = 10, intData2 = 20, intData3 = 30, intData4 = 40;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData5);
			childScope->Append(stringData2).PushBack(intData2);

			scope2.Append(stringData3).PushBack(intData3);
			Scope* childScope2 = &scope2.AppendScope(stringData6);
			childScope2->Append(stringData4).PushBack(intData4);

			Assert::IsFalse(scope == scope2);
			scope = scope2;
			Assert::IsTrue(scope == scope2);
		}

		TEST_METHOD(Scope_Equals)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2", stringData3 = "IntegerData3", stringData4 = "IntegerData4", stringData5 = "BabyScope", stringData6 = "BabyScope2";
			Scope scope, scope2;
			std::int32_t intData = 10, intData2 = 20, intData3 = 30, intData4 = 40;

			scope.Append(stringData).PushBack(intData);
			Scope* childScope = &scope.AppendScope(stringData5);
			childScope->Append(stringData2).PushBack(intData2);

			scope2.Append(stringData3).PushBack(intData3);
			Scope* childScope2 = &scope2.AppendScope(stringData6);
			childScope2->Append(stringData4).PushBack(intData4);

			Assert::IsFalse(scope.Equals(&scope2));
			scope = scope2;
			Assert::IsTrue(scope.Equals(&scope2));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}