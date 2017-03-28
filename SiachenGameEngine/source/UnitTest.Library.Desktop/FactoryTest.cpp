#include "pch.h"
#include "CppUnitTest.h"

#include "Factory.h"
#include "RTTI.h"
#include "Foo.h"
#include "HashMap.h"
#include "ConcreteProductBar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::Containers;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FactoryTest)
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

		TEST_METHOD(Factory_Add_Remove)
		{
			FooFactory fooFactory;
			Assert::IsTrue(Factory<RTTI>::Find("Foo") == &fooFactory);

			RTTI* productRTTI = Factory<RTTI>::Create("Foo");
			Assert::IsNotNull(productRTTI);
			Assert::IsTrue(productRTTI->Is("Foo"));

			delete productRTTI;


			ConcreteProductBarFactory barFactory;
			Assert::IsTrue(Factory<AbstractProductBar>::Find("ConcreteProductBar") == &barFactory);

			AbstractProductBar* product = Factory<AbstractProductBar>::Create("ConcreteProductBar");
			Assert::IsNotNull(product);

			delete product;
		}

		TEST_METHOD(Factory_Create)
		{
			FooFactory fooFactory;

			RTTI* product1 = Factory<RTTI>::Create("Foo");
			RTTI* product2 = Factory<RTTI>::Create("Foo");

			Assert::IsTrue(product1->Is("Foo"));
			Assert::IsTrue(product2->Is("Foo"));

			Assert::IsFalse(&product1 == &product2);

			delete product1;
			delete product2;


			ConcreteProductBarFactory barFactory;

			AbstractProductBar* product3 = Factory<AbstractProductBar>::Create("ConcreteProductBar");
			AbstractProductBar* product4 = Factory<AbstractProductBar>::Create("ConcreteProductBar");

			Assert::AreEqual(product3->GetInteger(), 0);
			Assert::AreEqual(product4->GetInteger(), 0);

			Assert::IsFalse(&product3 == &product4);

			delete product3;
			delete product4;
		}

		TEST_METHOD(Factory_ClassName)
		{
			FooFactory fooFactory;
			Assert::IsTrue(fooFactory.ClassName() == "Foo");

			ConcreteProductBarFactory barFactory;
			Assert::IsTrue(barFactory.ClassName() == "ConcreteProductBar");
		}

		TEST_METHOD(Factory_Find)
		{
			FooFactory fooFactory;
			Assert::IsTrue(Factory<RTTI>::Find("Foo") == &fooFactory);
		
			ConcreteProductBarFactory barFactory;
			Assert::IsTrue(Factory<AbstractProductBar>::Find("ConcreteProductBar") == &barFactory);
		}

		TEST_METHOD(Factory_Iterators)
		{
			FooFactory fooFactory;
			Assert::IsTrue((*Factory<RTTI>::begin()).first == "Foo");
			Assert::IsTrue((*Factory<RTTI>::begin()).second == &fooFactory);
			Assert::IsTrue(++Factory<RTTI>::begin() == Factory<RTTI>::end());

			ConcreteProductBarFactory barFactory;
			Assert::IsTrue((*Factory<AbstractProductBar>::begin()).first == "ConcreteProductBar");
			Assert::IsTrue((*Factory<AbstractProductBar>::begin()).second == &barFactory);
			Assert::IsTrue(++Factory<AbstractProductBar>::begin() == Factory<AbstractProductBar>::end());
		}

		TEST_METHOD(Factory_RTTI)
		{
			RTTI* fooAsRTTI = new Foo;

			Assert::IsTrue(fooAsRTTI->Is("Foo"));
			Assert::IsTrue(fooAsRTTI->Is(Foo::TypeIdClass()));
			Assert::IsNotNull(fooAsRTTI->As<Foo>());
			Assert::IsNotNull(fooAsRTTI->QueryInterface(Foo::TypeIdClass()));

			delete fooAsRTTI;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FactoryTest::sStartMemState;
};