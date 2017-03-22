#include "pch.h"
#include "CppUnitTest.h"

#include "Attributed.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "AttributedBaz.h"

#include "Datum.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Attributed_ClassInitialize)
		{
			AttributedFoo foo;
			AttributedBar bar;
			AttributedBaz baz;
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

			Assert::IsTrue(foo.IsPrescribedAttribute("this"));
			Assert::IsTrue(foo.IsPrescribedAttribute("mInteger"));
			Assert::IsFalse(foo.IsPrescribedAttribute("mFloat"));

			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryFoo"));

			AttributedBar bar;

			Assert::IsTrue(bar.IsPrescribedAttribute("this"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mInteger"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mFloat"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mString"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mVec4"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mMat4x4"));
			Assert::IsTrue(bar.IsPrescribedAttribute("mRTTI"));
			Assert::IsFalse(bar.IsPrescribedAttribute("mSomething"));

			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::IsFalse(bar.IsPrescribedAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attributed_IsAttribute)
		{
			AttributedFoo foo;
			
			Assert::IsTrue(foo.IsAttribute("this"));
			Assert::IsTrue(foo.IsAttribute("mInteger"));
			Assert::IsFalse(foo.IsAttribute("mFloat"));

			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::IsTrue(foo.IsAttribute("AuxiliaryFoo"));

			AttributedBar bar;

			Assert::IsTrue(bar.IsAttribute("this"));
			Assert::IsTrue(bar.IsAttribute("mInteger"));
			Assert::IsTrue(bar.IsAttribute("mFloat"));
			Assert::IsTrue(bar.IsAttribute("mString"));
			Assert::IsTrue(bar.IsAttribute("mVec4"));
			Assert::IsTrue(bar.IsAttribute("mMat4x4"));
			Assert::IsTrue(bar.IsAttribute("mRTTI"));
			Assert::IsFalse(bar.IsAttribute("mSomething"));

			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::IsTrue(bar.IsAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attributed_IsAuxiliaryAttribute)
		{
			AttributedFoo foo;

			Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("mInteger"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("mFloat"));

			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryFoo"));

			AttributedBar bar;

			Assert::IsFalse(bar.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mInteger"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mFloat"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mString"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mVec4"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mMat4x4"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mRTTI"));
			Assert::IsFalse(bar.IsAuxiliaryAttribute("mSomething"));

			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::IsTrue(bar.IsAuxiliaryAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attributed_AppendAuxiliaryAttribute)
		{
			AttributedFoo foo;

			Assert::IsTrue(foo.IsPrescribedAttribute("mInteger"));
			auto fooExpression = [&foo] { foo.AppendAuxiliaryAttribute("mInteger"); };
			Assert::ExpectException<std::exception>(fooExpression);

			Assert::IsFalse(foo.IsAuxiliaryAttribute("AuxiliaryFoo"));
			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryFoo"));
			Assert::IsTrue(foo.IsAttribute("AuxiliaryFoo"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryFoo"));

			AttributedBar bar;

			Assert::IsTrue(bar.IsPrescribedAttribute("mInteger"));
			auto barExpression = [&bar] { bar.AppendAuxiliaryAttribute("mInteger"); };
			Assert::ExpectException<std::exception>(barExpression);

			Assert::IsFalse(bar.IsAuxiliaryAttribute("AuxiliaryBar"));
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::IsTrue(bar.IsAuxiliaryAttribute("AuxiliaryBar"));
			Assert::IsTrue(bar.IsAttribute("AuxiliaryBar"));
			Assert::IsFalse(bar.IsPrescribedAttribute("AuxiliaryBar"));
		}

		TEST_METHOD(Attribute_AuxiliaryBegin)
		{
			AttributedFoo foo;

			Assert::AreEqual(2U, foo.AuxiliaryBegin());
			foo.AppendAuxiliaryAttribute("AuxiliaryFoo");
			Assert::AreEqual(2U, foo.AuxiliaryBegin());

			AttributedBar bar;

			Assert::AreEqual(7U, bar.AuxiliaryBegin());
			bar.AppendAuxiliaryAttribute("AuxiliaryBar");
			Assert::AreEqual(7U, bar.AuxiliaryBegin());
		}

		TEST_METHOD(Attributed_UpdatingValues)
		{
			AttributedFoo foo;

			//Updating external integers
			Assert::AreNotEqual(foo["mInteger"].Get<std::int32_t>(), 10);
			foo.SetInteger(10);
			Assert::AreEqual(foo["mInteger"].Get<std::int32_t>(), 10);

			Assert::AreNotEqual(foo.GetInteger(), 20);
			foo["mInteger"].Set(20);
			Assert::AreEqual(foo.GetInteger(), 20);

			AttributedBar bar;

			//Updating external floats
			Assert::AreNotEqual(bar["mFloat"].Get<std::float_t>(), 10.0f);
			bar.SetFloat(10.0f);
			Assert::AreEqual(bar["mFloat"].Get<std::float_t>(), 10.0f);

			Assert::AreNotEqual(bar.GetFloat(), 20.0f);
			bar["mFloat"].Set(20.0f);
			Assert::AreEqual(bar.GetFloat(), 20.0f);

			//Updating external strings
			Assert::IsFalse(bar["mString"].Get<std::string>() == "Ayy");
			bar.SetString("Ayy");
			Assert::IsTrue(bar["mString"].Get<std::string>() == "Ayy");

			Assert::IsFalse(bar.GetString() == "Jawohl");
			bar["mString"].Set("Jawohl");
			Assert::IsTrue(bar.GetString() == "Jawohl");

			//Updating external vectors
			glm::vec4 vec(10.0f, 11.0f, 12.0f, 13.0f), vec2(20.0f, 21.0f, 22.0f, 23.0f);
			
			Assert::AreNotEqual(bar["mVec4"].Get<glm::vec4>().x, vec.x);
			bar.SetVector(vec);
			Assert::AreEqual(bar["mVec4"].Get<glm::vec4>().x, vec.x);

			Assert::AreNotEqual(bar.GetVector().x, vec2.x);
			bar["mVec4"].Set(vec2);
			Assert::AreEqual(bar.GetVector().x, vec2.x);

			//Updating external matrices
			glm::mat4x4 mat(vec, vec, vec2, vec2), mat2(vec2, vec2, vec, vec);

			Assert::AreNotEqual(bar["mMat4x4"].Get<glm::mat4x4>()[0].x, vec.x);
			bar.SetMatrix(mat);
			Assert::AreEqual(bar["mMat4x4"].Get<glm::mat4x4>()[0].x, vec.x);

			Assert::AreNotEqual(bar.GetMatrix()[0].x, vec2.x);
			bar["mMat4x4"].Set(mat2);
			Assert::AreEqual(bar.GetMatrix()[0].x, vec2.x);

			//Updating external RTTI Foos
			Foo foo2(20);
			RTTI* fooPtr = &foo2;

			Foo* prevFoo = bar["mRTTI"].Get<RTTI*>()->As<Foo>();

			Assert::AreNotEqual(bar["mRTTI"].Get<RTTI*>()->As<Foo>()->GetValue(), 10);
			bar.SetRTTIFoo(10);
			Assert::AreEqual(bar["mRTTI"].Get<RTTI*>()->As<Foo>()->GetValue(), 10);

			Assert::AreNotEqual(bar.GetRTTIFoo(), 20);
			bar["mRTTI"].Set(fooPtr);
			Assert::AreEqual(bar.GetRTTIFoo(), 20);

			bar["mRTTI"].Set(prevFoo);
		}

		TEST_METHOD(Attributed_AddInternalAttribute)
		{
			AttributedBaz baz;

			Assert::IsTrue(baz.IsPrescribedAttribute("this"));

			Assert::IsTrue(baz.IsPrescribedAttribute("iInt"));
			Assert::IsTrue(baz.IsPrescribedAttribute("iFloat"));
			Assert::IsTrue(baz.IsPrescribedAttribute("iString"));
			Assert::IsTrue(baz.IsPrescribedAttribute("iVector"));
			Assert::IsTrue(baz.IsPrescribedAttribute("iMatrix"));
			Assert::IsTrue(baz.IsPrescribedAttribute("iRTTI"));
			Assert::IsTrue(baz.IsPrescribedAttribute("iScope"));

			Assert::AreEqual(baz["iRTTI"].Get<RTTI*>()->As<Foo>()->GetValue(), 321);
			Assert::IsTrue(baz["iScope"].Get<Scope*>()->Append("Butter").Get<std::string>() == "Chicken");

			Assert::AreEqual(9U, baz.AuxiliaryBegin());
			baz.AppendAuxiliaryAttribute("AuxiliaryBaz");
			Assert::AreEqual(9U, baz.AuxiliaryBegin());
		}

		TEST_METHOD(Attributed_CopyConstructor)
		{
			//Tests for attributed foo
			AttributedFoo foo;

			foo.AppendAuxiliaryAttribute("Butter") = "Chicken";
			foo.SetInteger(10);

			Assert::IsTrue(foo.IsAuxiliaryAttribute("Butter"));
			Assert::AreEqual(foo["mInteger"].Get<std::int32_t>(), 10);

			AttributedFoo foo2(foo);

			Assert::IsTrue(foo2["Butter"].Get<std::string>() == "Chicken");
			Assert::AreEqual(foo.AuxiliaryBegin(), 2U);

			Assert::IsTrue(foo2.IsAuxiliaryAttribute("Butter"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("mInteger"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("mInteger"));
			Assert::IsFalse(foo2.IsPrescribedAttribute("Butter"));

			Assert::AreEqual(foo2.GetInteger(), 10);

			foo2.SetInteger(20);
			Assert::AreEqual(foo.GetInteger(), 10);
			Assert::AreEqual(foo2.GetInteger(), 20);

			//Tests for class derived from attributed foo
			AttributedBar bar;

			bar.AppendAuxiliaryAttribute("Chicken") = "Tikka";
			bar.SetFloat(1.5f);

			AttributedBar bar2(bar);

			Assert::IsTrue(bar2.IsAuxiliaryAttribute("Chicken"));
			Assert::AreEqual(bar2.AuxiliaryBegin(), 7U);

			Assert::IsTrue(bar2.IsAuxiliaryAttribute("Chicken"));
			Assert::IsFalse(bar2.IsPrescribedAttribute("Chicken"));
			Assert::IsTrue(bar2.IsPrescribedAttribute("mRTTI"));
			Assert::IsFalse(bar2.IsAuxiliaryAttribute("mRTTI"));

			Assert::AreEqual(bar2.GetFloat(), 1.5f);
			bar2.SetFloat(3.0f);
			Assert::AreEqual(bar2.GetFloat(), 3.0f);
			Assert::AreEqual(bar.GetFloat(), 1.5f);
		}

		TEST_METHOD(Attributed_AssignmentOperator)
		{
			//Tests for attributed foo
			AttributedFoo foo;

			foo.AppendAuxiliaryAttribute("Butter") = "Chicken";
			foo.SetInteger(10);

			Assert::IsTrue(foo.IsAuxiliaryAttribute("Butter"));
			Assert::AreEqual(foo["mInteger"].Get<std::int32_t>(), 10);

			AttributedFoo foo2;
			foo2.AppendAuxiliaryAttribute("Yellow");
			foo2 = foo;
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("Yellow"));

			Assert::IsTrue(foo2["Butter"].Get<std::string>() == "Chicken");
			Assert::AreEqual(foo.AuxiliaryBegin(), 2U);

			Assert::IsTrue(foo2.IsAuxiliaryAttribute("Butter"));
			Assert::IsTrue(foo2.IsPrescribedAttribute("mInteger"));
			Assert::IsFalse(foo2.IsAuxiliaryAttribute("mInteger"));
			Assert::IsFalse(foo2.IsPrescribedAttribute("Butter"));

			Assert::AreEqual(foo2.GetInteger(), 10);

			foo2.SetInteger(20);
			Assert::AreEqual(foo.GetInteger(), 10);
			Assert::AreEqual(foo2.GetInteger(), 20);

			//Tests for class derived from attributed foo
			AttributedBar bar;

			bar.AppendAuxiliaryAttribute("Chicken") = "Tikka";
			bar.SetFloat(1.5f);

			AttributedBar bar2;
			bar2 = bar;

			Assert::IsTrue(bar2.IsAuxiliaryAttribute("Chicken"));
			Assert::AreEqual(bar2.AuxiliaryBegin(), 7U);

			Assert::IsTrue(bar2.IsAuxiliaryAttribute("Chicken"));
			Assert::IsFalse(bar2.IsPrescribedAttribute("Chicken"));
			Assert::IsTrue(bar2.IsPrescribedAttribute("mRTTI"));
			Assert::IsFalse(bar2.IsAuxiliaryAttribute("mRTTI"));

			Assert::AreEqual(bar2.GetFloat(), 1.5f);
			bar2.SetFloat(3.0f);
			Assert::AreEqual(bar2.GetFloat(), 3.0f);
			Assert::AreEqual(bar.GetFloat(), 1.5f);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedTest::sStartMemState;
}