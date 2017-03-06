#include "pch.h"
#include "CppUnitTest.h"

#include "Attributed.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedTest)
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

		TEST_METHOD(Attributed_First)
		{
			AttributedFoo foo;
			AttributedBar bar;
			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attributed_Second)
		{
			AttributedFoo foo;
			AttributedFoo foo2;
			AttributedBar bar;
			AttributedBar bar2;
			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attributed_IsPrescribedAttribute)
		{
			AttributedFoo foo;
			AttributedBar bar;

			Assert::IsTrue(foo.IsPrescribedAttribute("this"));
			Assert::IsTrue(foo.IsPrescribedAttribute("mInteger"));
			Assert::IsFalse(foo.IsPrescribedAttribute("mFloat"));


			Assert::IsTrue(bar.IsPrescribedAttribute("this"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mInteger"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mFloat"));
			Assert::IsFalse(bar.IsPrescribedAttribute("mSomething"));

			foo.AppendAuxillaryAttribute("AuxillaryFoo");
			bar.AppendAuxillaryAttribute("AuxillaryBar");

			Assert::IsFalse(foo.IsPrescribedAttribute("AuxillaryFoo"));
			Assert::IsFalse(bar.IsPrescribedAttribute("AuxillaryBar"));

			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attributed_IsAttribute)
		{
			AttributedFoo foo;
			AttributedBar bar;

			Assert::IsTrue(foo.IsAttribute("this"));
			Assert::IsTrue(foo.IsAttribute("mInteger"));
			Assert::IsFalse(foo.IsAttribute("mFloat"));

			Assert::IsTrue(bar.IsAttribute("this"));
			Assert::IsTrue(bar.IsAttribute("mInteger"));
			Assert::IsTrue(bar.IsAttribute("mFloat"));
			Assert::IsFalse(bar.IsAttribute("mSomething"));

			foo.AppendAuxillaryAttribute("AuxillaryFoo");
			bar.AppendAuxillaryAttribute("AuxillaryBar");

			Assert::IsTrue(foo.IsAttribute("AuxillaryFoo"));
			Assert::IsTrue(bar.IsAttribute("AuxillaryBar"));

			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attributed_IsAuxillaryAttribute)
		{
			AttributedFoo foo;
			AttributedBar bar;

			Assert::IsFalse(foo.IsAuxillaryAttribute("this"));
			Assert::IsFalse(foo.IsAuxillaryAttribute("mInteger"));
			Assert::IsFalse(foo.IsAuxillaryAttribute("mFloat"));

			Assert::IsFalse(bar.IsAuxillaryAttribute("this"));
			Assert::IsFalse(bar.IsAuxillaryAttribute("mInteger"));
			Assert::IsFalse(bar.IsAuxillaryAttribute("mFloat"));
			Assert::IsFalse(bar.IsAuxillaryAttribute("mSomething"));

			foo.AppendAuxillaryAttribute("AuxillaryFoo");
			bar.AppendAuxillaryAttribute("AuxillaryBar");

			Assert::IsTrue(foo.IsAuxillaryAttribute("AuxillaryFoo"));
			Assert::IsTrue(bar.IsAuxillaryAttribute("AuxillaryBar"));

			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attributed_AppendAuxillaryAttribute)
		{
			AttributedFoo foo;

			Assert::IsFalse(foo.IsAuxillaryAttribute("mInteger"));
			auto fooExpression = [&foo] { foo.AppendAuxillaryAttribute("mInteger"); };
			Assert::ExpectException<std::exception>(fooExpression);

			Assert::IsFalse(foo.IsAuxillaryAttribute("AuxillaryFoo"));
			foo.AppendAuxillaryAttribute("AuxillaryFoo");
			Assert::IsTrue(foo.IsAuxillaryAttribute("AuxillaryFoo"));

			AttributedBar bar;

			Assert::IsFalse(bar.IsAuxillaryAttribute("mInteger"));
			auto barExpression = [&bar] { bar.AppendAuxillaryAttribute("mInteger"); };
			Assert::ExpectException<std::exception>(barExpression);

			Assert::IsFalse(bar.IsAuxillaryAttribute("AuxillaryBar"));
			bar.AppendAuxillaryAttribute("AuxillaryBar");
			Assert::IsTrue(bar.IsAuxillaryAttribute("AuxillaryBar"));

			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attribute_AuxillaryBegin)
		{
			AttributedFoo foo;

			Assert::AreEqual(2U, foo.AuxillaryBegin());
			foo.AppendAuxillaryAttribute("AuxillaryFoo");
			Assert::AreEqual(2U, foo.AuxillaryBegin());

			AttributedBar bar;

			Assert::AreEqual(3U, bar.AuxillaryBegin());
			bar.AppendAuxillaryAttribute("AuxillaryBar");
			Assert::AreEqual(3U, bar.AuxillaryBegin());

			//Attributed::ClearCacheHashmap();
		}

		TEST_METHOD(Attribute_ClearCacheHashmap)
		{
			AttributedFoo foo;
			AttributedBar bar;

			Attributed::ClearCacheHashmap();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}