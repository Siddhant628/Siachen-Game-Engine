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
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			AttributedFoo foo;
			AttributedBar bar;
		}

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

			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");

			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryFoo"));
			Assert::IsFalse(bar.IsPrescribedAttribute("AuxiliaryBar"));
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

			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");

			Assert::IsTrue(foo.IsAttribute("AuxiliaryFoo"));
			Assert::IsTrue(bar.IsAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attributed_IsAuxiliaryAttribute)
		{
			AttributedFoo foo;
			AttributedBar bar;

			Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("mInteger"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("mFloat"));

			Assert::IsFalse(bar.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mInteger"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mFloat"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mSomething"));

			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");

			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryFoo"));
			Assert::IsTrue(bar.IsAuxiliaryAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attributed_AppendAuxiliaryAttribute)
		{
			AttributedFoo foo;

			Assert::IsFalse(foo.IsAuxiliaryAttribute("mInteger"));
			auto fooExpression = [&foo] { foo.AppendAuxiliaryAttribute("mInteger"); };
			Assert::ExpectException<std::exception>(fooExpression);

			Assert::IsFalse(foo.IsAuxiliaryAttribute("AuxiliaryFoo"));
			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryFoo"));

			AttributedBar bar;

			Assert::IsFalse(bar.IsAuxiliaryAttribute("mInteger"));
			auto barExpression = [&bar] { bar.AppendAuxiliaryAttribute("mInteger"); };
			Assert::ExpectException<std::exception>(barExpression);

			Assert::IsFalse(bar.IsAuxiliaryAttribute("AuxiliaryBar"));
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::IsTrue(bar.IsAuxiliaryAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attribute_AuxiliaryBegin)
		{
			AttributedFoo foo;

			Assert::AreEqual(2U, foo.AuxiliaryBegin());
			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::AreEqual(2U, foo.AuxiliaryBegin());

			AttributedBar bar;

			Assert::AreEqual(3U, bar.AuxiliaryBegin());
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::AreEqual(3U, bar.AuxiliaryBegin());
		}

		TEST_METHOD(Attributed_UpdatingValues)
		{
			AttributedFoo foo;

			foo.SetInteger(10);
			Assert::AreEqual(foo["mInteger"].Get<std::int32_t>(), 10);

			foo["mInteger"].Set(20);
			Assert::AreEqual(foo.GetInteger(), 20);

			AttributedBar bar;

			bar.SetFloat(10.0f);
			Assert::AreEqual(bar["mFloat"].Get<std::float_t>(), 10.0f);

			bar["mFloat"].Set(20.0f);
			Assert::AreEqual(bar.GetFloat(), 20.0f);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}