#include "pch.h"
#include "CppUnitTest.h"

#include "Action.h"
#include "ActionList.h"
#include "ActionFoo.h"
#include "ActionIf.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"

#include "World.h"
#include "EntityFoo.h"
#include "Factory.h"
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
			ActionList list;
			ActionIf aIf;
			ActionCreateAction aCreate;
			ActionDestroyAction aDestroy;
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
			ActionListFactory actionListFactory;

			Action* actionList = world.CreateAction("ActionList", "list");
			Assert::IsTrue(actionList->Is(ActionList::TypeIdClass()));
			// CreateAction()
			Action* listAction1 = static_cast<ActionList*>(actionList)->CreateAction("ActionFoo", "foo1");
			Action* listAction2 = static_cast<ActionList*>(actionList)->CreateAction("ActionFoo", "foo2");
			// Actions(), Datum access
			Assert::AreEqual(static_cast<ActionList*>(actionList)->Actions().Size(), 2U);
			Assert::AreEqual(static_cast<ActionList*>(actionList)->Append("actions").Size(), 2U);
			// Update()
			static_cast<ActionFoo*>(listAction1)->mString = "foo1";
			static_cast<ActionFoo*>(listAction2)->mString = "foo2";
			WorldState state;
			actionList->Update(state);
		}

		TEST_METHOD(Action_World)
		{
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;

			//CreateAction()
			world.CreateAction("ActionFoo", "foo1");
			world.CreateAction("ActionFoo", "foo2");
			// Actions(), Populate()
			Assert::IsTrue(static_cast<ActionFoo*>(world.Append("actions").Get<Scope*>())->Name() == "foo1");
			Assert::IsTrue(static_cast<ActionFoo*>(world.Append("actions").Get<Scope*>(1))->Name() == "foo2");
			Assert::IsTrue(&world.Actions() == &world.Append("actions"));
			// Update()
			WorldState worldState;
			world.CreateSector("Sector1");
			world.Update(worldState);
		}

		TEST_METHOD(Action_Sector)
		{
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;

			Sector* sector1 = world.CreateSector("Sector1");
			// CreateAction()
			sector1->CreateAction("ActionFoo", "foo1");
			sector1->CreateAction("ActionFoo", "foo2");
			// Actions(), Populate()
			Assert::IsTrue(static_cast<ActionFoo*>(sector1->Append("actions").Get<Scope*>())->Name() == "foo1");
			Assert::IsTrue(static_cast<ActionFoo*>(sector1->Append("actions").Get<Scope*>(1))->Name() == "foo2");
			Assert::IsTrue(&sector1->Actions() == &sector1->Append("actions"));
			// Update()
			static_cast<ActionFoo*>(sector1->Append("actions").Get<Scope*>())->mString = "One";
			static_cast<ActionFoo*>(sector1->Append("actions").Get<Scope*>(1))->mString = "Two";
			WorldState worldState;
			sector1->Update(worldState);
		}

		TEST_METHOD(Action_Entity)
		{
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;

			Sector* sector1 = world.CreateSector("Sector1");
			Entity* entity1 = sector1->CreateEntity("EntityFoo", "eFoo1");
			// CreateAction()
			entity1->CreateAction("ActionFoo", "foo1");
			entity1->CreateAction("ActionFoo", "foo2");
			// Actions(), Populate()
			Assert::IsTrue(static_cast<ActionFoo*>(entity1->Append("actions").Get<Scope*>())->Name() == "foo1");
			Assert::IsTrue(static_cast<ActionFoo*>(entity1->Append("actions").Get<Scope*>(1))->Name() == "foo2");
			Assert::IsTrue(&entity1->Actions() == &entity1->Append("actions"));
			// Update()
			static_cast<ActionFoo*>(entity1->Append("actions").Get<Scope*>())->mString = "One";
			static_cast<ActionFoo*>(entity1->Append("actions").Get<Scope*>(1))->mString = "Two";
			WorldState worldState;
			entity1->Update(worldState);
		}

		TEST_METHOD(Action_ActionIf)
		{
			WorldState worldState;
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionIfFactory actionIfFactory;

			ActionIf* firstIf = static_cast<ActionIf*>(world.CreateAction("ActionIf", "firstIf"));
			ActionFoo* aThen = static_cast<ActionFoo*>(firstIf->CreateAction("ActionFoo", "foo1"));
			ActionFoo* aElse = static_cast<ActionFoo*>(firstIf->CreateAction("ActionFoo", "foo2"));
			aThen->mString = "Then";
			aElse->mString = "Else";

			// Prints then to output window
			firstIf->Append("condition").Set(1);
			firstIf->Update(worldState);
			// Prints else to output window
			firstIf->Append("condition").Set(0);
			firstIf->Update(worldState);
		}

		TEST_METHOD(Action_CreateAction)
		{
			WorldState worldState;
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionCreateActionFactory aCreateActionFactory;

			ActionCreateAction* actionCreate = static_cast<ActionCreateAction*>(world.CreateAction("ActionCreateAction", "firstActionCreate"));
			actionCreate->Append("className").Set("ActionFoo");
			actionCreate->Append("instanceName").Set("foo1");

			Assert::AreEqual(world.Actions().Size(), 1U);
			world.Update(worldState);
			Assert::AreEqual(world.Actions().Size(), 2U);

			Assert::IsTrue(world.Actions().Get<Scope*>(1)->Is(ActionFoo::TypeIdClass()));
			Assert::IsTrue(static_cast<ActionFoo*>(world.Actions().Get<Scope*>(1))->Name() == "foo1");
		}

		TEST_METHOD(Action_DestroyAction)
		{
			WorldState worldState;
			World world("World1");
			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionDestroyActionFactory aDestroyFactory;

			world.CreateAction("ActionFoo", "foo1");
			ActionDestroyAction* destroy = static_cast<ActionDestroyAction*>(world.CreateAction("ActionDestroyAction", "destroy1"));
			destroy->Append("actionName").Set("foo1");

			Assert::AreEqual(world.Actions().Size(), 2U);
			Assert::IsTrue(world.Actions().Get<Scope*>(1) == destroy);

			world.Update(worldState);

			Assert::AreEqual(world.Actions().Size(), 1U);
			Assert::IsTrue(world.Actions().Get<Scope*>(0) == destroy);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionTest::sStartMemState;
};