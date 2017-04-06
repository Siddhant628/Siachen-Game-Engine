#include "pch.h"
#include "CppUnitTest.h"

#include "Action.h"
#include "ActionList.h"
#include "ActionFoo.h"
#include "ActionIf.h"

#include "XmlSharedDataWorld.h"
#include "XmlParseHelperWorld.h"
#include "XmlParseHelperActionIf.h"
#include "SampleXmlSharedData.h"

#include "World.h"
#include "EntityFoo.h"
#include "Factory.h"
#include "RTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::HelperClasses;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ActionParsingTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ActionTest_Initialize)
		{
			World world("World");
			Sector sector;
			Entity entity;
			ActionFoo aFoo;
			EntityFoo eFoo;
			ActionList list;
			ActionIf actionIf;
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

		TEST_METHOD(ActionParsing_ActionList)
		{
			XmlSharedDataWorld sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperWorld worldHelper;
			parseMaster.AddHelper(worldHelper);

			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionListFactory aListFactory;

			parseMaster.ParseFromFile("XmlWithActionList.xml");

			World* world = static_cast<World*>(sharedData.mCurrentScope);
			Assert::AreEqual(world->Actions().Size(), 1U);
			Assert::IsTrue(world->Actions().Get<Scope*>()->Is(ActionList::TypeIdClass()));
			ActionList* list = static_cast<ActionList*>(world->Actions().Get<Scope*>());

			Assert::IsTrue(list->Name() == "list");
			Assert::AreEqual(list->Actions().Size(), 2U);

			Assert::IsTrue(static_cast<ActionFoo*>(list->Actions().Get<Scope*>())->Name() == "foo1");
			Assert::IsTrue(static_cast<ActionFoo*>(list->Actions().Get<Scope*>(1))->Name() == "foo2");
		}

		TEST_METHOD(ActionParsing_ActionsInsideWorldSectorEntity)
		{
			XmlSharedDataWorld sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperWorld worldHelper;
			parseMaster.AddHelper(worldHelper);

			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionListFactory aListFactory;

			parseMaster.ParseFromFile("XmlWithActionList.xml");
			World* world = static_cast<World*>(sharedData.mCurrentScope);

			Sector* sector1 = static_cast<Sector*>(world->Sectors().Get<Scope*>());
			Assert::IsTrue(static_cast<ActionFoo*>(sector1->Actions().Get<Scope*>())->Name() == "foo3");

			Entity* entity1 = static_cast<Entity*>(sector1->Entities().Get<Scope*>());
			Assert::IsTrue(static_cast<ActionFoo*>(entity1->Actions().Get<Scope*>())->Name() == "foo4");
		}

		TEST_METHOD(ActionParsing_ActionsIf)
		{
			XmlSharedDataWorld sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperWorld worldHelper;
			XmlParseHelperActionIf actionIfHelper;
			parseMaster.AddHelper(worldHelper);
			parseMaster.AddHelper(actionIfHelper);

			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionIfFactory aIfFactory;
			ActionListFactory aListFactory;

			parseMaster.ParseFromFile("XmlWithActionIf.xml");
			World* world = static_cast<World*>(sharedData.mCurrentScope);
			
			// ActionIf inside World
			ActionIf* actionIf1 = static_cast<ActionIf*>(world->Actions().Get<Scope*>());
			
			Assert::IsTrue(static_cast<ActionIf*>(world->Actions().Get<Scope*>())->Name() == "if1");
			Assert::IsTrue(static_cast<ActionIf*>(world->Actions().Get<Scope*>())->Append("condition").Get<std::int32_t>() == 1);
			Assert::IsTrue(static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>())->Name() == "thenFoo1");
			Assert::IsTrue(static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>(1))->Name() == "elseFoo1");

			static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>())->mString = "Then1\n";
			static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>(1))->mString = "Else1\n";
			
			// ActionIf inside Sector
			Sector* sector1 = static_cast<Sector*>(world->Sectors().Get<Scope*>());
			ActionIf* actionIf2 = static_cast<ActionIf*>(sector1->Actions().Get<Scope*>());
			static_cast<ActionFoo*>(actionIf2->Actions().Get<Scope*>())->mString = "Then2\n";
			static_cast<ActionFoo*>(actionIf2->Actions().Get<Scope*>(1))->mString = "Else2\n";

			// ActionIf inside Entity
			Entity* entity1 = static_cast<Entity*>(sector1->Entities().Get<Scope*>());
			ActionIf* actionIf3 = static_cast<ActionIf*>(entity1->Actions().Get<Scope*>());
			static_cast<ActionFoo*>(actionIf3->Actions().Get<Scope*>())->mString = "Then3\n";
			static_cast<ActionFoo*>(actionIf3->Actions().Get<Scope*>(1))->mString = "Else3\n";

			// ActionIf inside ActionList
			ActionIf* actionIf4 = static_cast<ActionIf*>(static_cast<ActionList*>(world->Actions().Get<Scope*>(1))->Actions().Get<Scope*>());
			static_cast<ActionFoo*>(actionIf4->Actions().Get<Scope*>())->mString = "Then4\n";
			static_cast<ActionFoo*>(actionIf4->Actions().Get<Scope*>(1))->mString = "Else4\n";

			WorldState worldState;
			world->Update(worldState);
		}

		TEST_METHOD(ActionParsing_ActionIfClone)
		{
			XmlSharedDataWorld sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperWorld worldHelper;
			XmlParseHelperActionIf actionIfHelper;
			parseMaster.AddHelper(worldHelper);
			parseMaster.AddHelper(actionIfHelper);

			ActionFooFactory aFooFactory;
			EntityFooFactory eFooFactory;
			ActionIfFactory aIfFactory;
			ActionListFactory aListFactory;

			XmlParseMaster* clonedParseMaster = parseMaster.Clone();

			clonedParseMaster->ParseFromFile("XmlWithActionIf.xml");
			World* world = static_cast<World*>(static_cast<XmlSharedDataWorld*>(clonedParseMaster->GetSharedData())->mCurrentScope);

			// ActionIf inside World
			ActionIf* actionIf1 = static_cast<ActionIf*>(world->Actions().Get<Scope*>());

			Assert::IsTrue(static_cast<ActionIf*>(world->Actions().Get<Scope*>())->Name() == "if1");
			Assert::IsTrue(static_cast<ActionIf*>(world->Actions().Get<Scope*>())->Append("condition").Get<std::int32_t>() == 1);
			Assert::IsTrue(static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>())->Name() == "thenFoo1");
			Assert::IsTrue(static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>(1))->Name() == "elseFoo1");

			static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>())->mString = "Then1\n";
			static_cast<ActionFoo*>(actionIf1->Actions().Get<Scope*>(1))->mString = "Else1\n";

			// ActionIf inside Sector
			Sector* sector1 = static_cast<Sector*>(world->Sectors().Get<Scope*>());
			ActionIf* actionIf2 = static_cast<ActionIf*>(sector1->Actions().Get<Scope*>());
			static_cast<ActionFoo*>(actionIf2->Actions().Get<Scope*>())->mString = "Then2\n";
			static_cast<ActionFoo*>(actionIf2->Actions().Get<Scope*>(1))->mString = "Else2\n";

			// ActionIf inside Entity
			Entity* entity1 = static_cast<Entity*>(sector1->Entities().Get<Scope*>());
			ActionIf* actionIf3 = static_cast<ActionIf*>(entity1->Actions().Get<Scope*>());
			static_cast<ActionFoo*>(actionIf3->Actions().Get<Scope*>())->mString = "Then3\n";
			static_cast<ActionFoo*>(actionIf3->Actions().Get<Scope*>(1))->mString = "Else3\n";

			// ActionIf inside ActionList
			ActionIf* actionIf4 = static_cast<ActionIf*>(static_cast<ActionList*>(world->Actions().Get<Scope*>(1))->Actions().Get<Scope*>());
			static_cast<ActionFoo*>(actionIf4->Actions().Get<Scope*>())->mString = "Then4\n";
			static_cast<ActionFoo*>(actionIf4->Actions().Get<Scope*>(1))->mString = "Else4\n";

			WorldState worldState;
			world->Update(worldState);

			delete clonedParseMaster;
		}

		TEST_METHOD(ActionParsing_HelperInitialize)
		{
			SampleXmlSharedData sharedData;
			XmlParseHelperActionIf ifHelper;

			auto expression1 = [&ifHelper, &sharedData] {ifHelper.Initialize(sharedData); };
			Assert::ExpectException<std::runtime_error>(expression1);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionParsingTest::sStartMemState;
};