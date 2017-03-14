#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "Datum.h"
#include "Foo.h"

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

			scope[stringData] = intData;
			Datum scopeDatum = scope.Append(stringData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(), intData);

			scope.Append(stringData).PushBack(intData2);
			scopeDatum = scope.Append(stringData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(), intData);
			Assert::AreEqual(scopeDatum.Get<std::int32_t>(1U), intData2);
		}

		TEST_METHOD(Scope_AppendScope)
		{
			Scope scope;

			scope["Health"] = 100;
			auto appendExpression = [&scope] { scope.AppendScope("Health"); };
			Assert::ExpectException<std::exception>(appendExpression);

			Scope& scopeRef = scope.AppendScope("ChildScope");
			scopeRef.Append("Damage1") = 10;
			Assert::AreEqual(scope.Append("ChildScope").Get<Scope*>()->Append("Damage1").Get<std::int32_t>(), 10);

			Scope& scopeRef2 = scope.AppendScope("ChildScope");
			scopeRef2.Append("Damage2") = 20;
			Assert::AreEqual(scope.Append("ChildScope").Get<Scope*>(1)->Append("Damage2").Get<std::int32_t>(), 20);

			Vector<std::string> keys;
			
			scopeRef.GetKeys(keys);
			Assert::AreEqual(keys.Size(), 1U);
			Assert::IsTrue(keys.At(0) == "Damage1");

			scopeRef2.GetKeys(keys);
			Assert::AreEqual(keys.Size(), 1U);
			Assert::IsTrue(keys.At(0) == "Damage2");

			scope.GetKeys(keys);
			Assert::AreEqual(keys.Size(), 2U);
			Assert::AreEqual(scope.Append("ChildScope").Size(), 2U);
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

			auto scopeExpression = [&scope, &stringData] {scope.Adopt(scope, stringData); };
			Assert::ExpectException<std::exception>(scopeExpression);

			Scope scope3;
			scope3["Integer"] = 10;
			auto scopeExpression2 = [&scope3, &scope] {scope3.Adopt(scope, "Integer"); };
			Assert::ExpectException<std::exception>(scopeExpression2);
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

		TEST_METHOD(Scope_ToString)
		{
			std::string stringData = "IntegerData", stringData2 = "IntegerData2";
			Scope scope;
			std::int32_t intData = 10, intData2 = 20;

			scope.Append(stringData).PushBack(intData);
			Assert::IsTrue(scope.ToString() == "Scope(1)");

			scope.Append(stringData).PushBack(intData2);
			Assert::IsTrue(scope.ToString() == "Scope(1)");

			scope.Append(stringData2).PushBack(intData);
			Assert::IsTrue(scope.ToString() == "Scope(2)");

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

		TEST_METHOD(Scope_RTTI)
		{
			RTTI* scopeAsRTTI = new Scope;

			Assert::IsTrue(scopeAsRTTI->Is("Scope"));
			Assert::IsFalse(scopeAsRTTI->Is("Foo"));

			Assert::IsTrue(scopeAsRTTI->Is(Scope::TypeIdClass()));
			Assert::IsFalse(scopeAsRTTI->Is(SiachenGameEngine::HelperClasses::Foo::TypeIdClass()));

			Assert::IsNotNull(scopeAsRTTI->As<Scope>());
			Assert::IsNull(scopeAsRTTI->As<SiachenGameEngine::HelperClasses::Foo>());

			delete scopeAsRTTI;
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

		TEST_METHOD(Scope_GetKeys)
		{
			Scope scope;
			Vector<std::string> scopeKeys;

			scope.GetKeys(scopeKeys);
			Assert::IsTrue(scopeKeys.IsEmpty());

			scope["first"] = 1;
			scope.GetKeys(scopeKeys);
			Assert::IsFalse(scopeKeys.IsEmpty());
			Assert::AreEqual(1U, scopeKeys.Size());

			scope["second"] = 2;
			scope.GetKeys(scopeKeys);
			Assert::AreEqual(2U, scopeKeys.Size());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}