#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "EntityFoo.h"
#include "Datum.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::Containers;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EntityTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Entity_ClassInitialize)
		{
			World world("World");
			Sector sector;
			Entity entity;
			EntityFoo entityFoo;
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

		TEST_METHOD(Entity_World_NameMethods)
		{
			auto constructorExpression = [] {World invalidWorld(""); };
			Assert::ExpectException<std::runtime_error>(constructorExpression);

			World world("world");

			// Name()
			Assert::IsTrue(world.Name() == "world");
			Assert::IsTrue(world["name"].Get<std::string>() == "world");
			
			// SetName()
			world.SetName("newName");

			Assert::IsTrue(world.Name() == "newName");
			Assert::IsTrue(world["name"].Get<std::string>() == "newName");
		}

		TEST_METHOD(Entity_World_SectorMethods)
		{
			World world("world");

			Assert::IsTrue(world.Sectors().IsEmpty());
			Assert::IsTrue(world.Sectors().Type() == DatumType::TableType);

			// CreateSector()
			Sector* sector1 = world.CreateSector("sector1");
			Assert::AreEqual(world.Sectors().Size(), 1U);

			// AdoptSector()
			Sector* sector2 = new Sector();
			sector2->SetName("sector2");
			world.AdoptSector(*sector2);
			
			// Sectors()
			Assert::AreEqual(world.Sectors().Size(), 2U);

			Assert::IsTrue(sector1 == world.Sectors().Get<Scope*>());
			Assert::IsTrue(sector2 == world.Sectors().Get<Scope*>(1));
			Assert::IsTrue(sector1 == world.Find("sectors")->Get<Scope*>());
			Assert::IsTrue(sector2 == world.Find("sectors")->Get<Scope*>(1));
		}

		TEST_METHOD(Entity_World_Update)
		{
			World world("world");
			WorldState worldState;
			EntityFooFactory entityFooFactory;

			Sector* sector1 = world.CreateSector("sector1");
			world.CreateSector("sector2");

			sector1->CreateEntity("EntityFoo", "entity1");

			world.Update(worldState);
		}

		TEST_METHOD(Entity_First)
		{
			World world("firstWorld");
			EntityFooFactory entityFooFactory;

			Sector* sector =  world.CreateSector("firstSector");
			Entity* entity = sector->CreateEntity("EntityFoo", "firstEntity");
			
			Assert::IsTrue(world.Sectors().Get<Scope*>() == sector);
			Assert::IsTrue(&world.Sectors() == world.Find("sectors"));

			Assert::IsTrue(entity->Is(EntityFoo::TypeIdClass()));
			(static_cast<EntityFoo*>(entity))->mInt = 10;
			(static_cast<EntityFoo*>(entity))->mFloat = 20.0f;

			Assert::AreEqual(static_cast<EntityFoo*>(static_cast<Sector*>(world.Sectors().Get<Scope*>())->Entities().Get<Scope*>())->mInt, 10);
			Assert::AreEqual(static_cast<EntityFoo*>(static_cast<Sector*>(world.Sectors().Get<Scope*>())->Entities().Get<Scope*>())->mFloat, 20.0f);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityTest::sStartMemState;
};