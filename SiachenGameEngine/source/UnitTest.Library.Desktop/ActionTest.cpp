#include "pch.h"
#include "CppUnitTest.h"

#include "Action.h"
#include "ActionList.h"
#include "ActionFoo.h"

#include "World.h"
#include "EntityFoo.h"
#include "RTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ActionTest)
	{
	public:

		TEST_CLASS_INITIALIZE(Action_Initialize)
		{
			World world("World");
			Sector sector;
			Entity entity;
			ActionFoo aFoo;
			EntityFoo eFoo;
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

		TEST_METHOD(Action_NameMethods)
		{
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;

			Action* action = world.CreateAction("ActionFoo", "firstAction");
			Assert::IsTrue(action->Name() == "firstAction");
			action->SetName("firstChanged");
			Assert::IsTrue(action->Name() == "firstChanged");
			Assert::IsTrue(action->Append("name").Get<std::string>() == "firstChanged");
			Assert::IsTrue(action->Is(ActionFoo::TypeIdClass()));

			Sector* sector = world.CreateSector("Sector1");
			Action* action2 = sector->CreateAction("ActionFoo", "secondAction"); 
			Assert::IsTrue(action2->Name() == "secondAction");
			action2->SetName("secondChanged");
			Assert::IsTrue(action2->Name() == "secondChanged");
			Assert::IsTrue(action2->Append("name").Get<std::string>() == "secondChanged");
			Assert::IsTrue(action2->Is(ActionFoo::TypeIdClass()));

			Entity* entity = sector->CreateEntity("EntityFoo", "firstEntity");
			Action* action3 = entity->CreateAction("ActionFoo", "thirdAction");
			Assert::IsTrue(action3->Name() == "thirdAction");
			action3->SetName("thirdChanged");
			Assert::IsTrue(action3->Name() == "thirdChanged");
			Assert::IsTrue(action3->Append("name").Get<std::string>() == "thirdChanged");
			Assert::IsTrue(action3->Is(ActionFoo::TypeIdClass()));
		}

		TEST_METHOD(Action_ActionList)
		{
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			//ActionListFactory actionListFactory;

			//Action* actionList = world.CreateAction("ActionList", "list");
			//Assert::IsTrue(actionList->Is(ActionList::TypeIdClass()));
			//
			//static_cast<ActionList*>(actionList)->CreateAction("ActionFoo", "foo1");
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionTest::sStartMemState;
};