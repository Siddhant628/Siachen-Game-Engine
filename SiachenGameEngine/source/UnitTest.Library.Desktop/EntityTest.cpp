#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "EntityFoo.h"
#include "Datum.h"
#include "Foo.h"
#include "GameClock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::Library;

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

		TEST_METHOD(Entity_Sector_NameMethods)
		{
			World world("world");
			Sector* sector1 = world.CreateSector("sector1");
			Sector* sector2 = world.CreateSector("sector2");

			Assert::IsTrue(sector1->Name() == "sector1");
			Assert::IsTrue(sector2->Name() == "sector2");
		
			sector1->SetName("newName1");
			sector2->SetName("newName2");

			Assert::IsTrue(sector1->Name() == "newName1");
			Assert::IsTrue(sector2->Name() == "newName2");
		}

		TEST_METHOD(Entity_Sector_EntityMethods)
		{
			World world("world");
			EntityFooFactory entityFooFactory;

			Sector* sector1 = world.CreateSector("sector1");
			Sector* sector2 = world.CreateSector("sector2");
			Entity* entity1 = sector1->CreateEntity("EntityFoo", "entity1");

			// Entities()
			Assert::AreEqual(sector1->Entities().Size(), 1U);
			Assert::IsTrue(sector2->Entities().IsEmpty());
			Assert::IsTrue(sector1->Entities().Get<Scope*>() == entity1);

			// CreateEntity()
			Entity* entity2 = sector1->CreateEntity("EntityFoo", "entity2");

			Assert::AreEqual(sector1->Entities().Size(), 2U);
			Assert::IsTrue(sector1->Entities().Get<Scope*>(1) == entity2);

			// AdoptEntity()
			Entity* entity3 = new EntityFoo();
			(static_cast<EntityFoo*>(entity3))->mInt = 10;
			(static_cast<EntityFoo*>(entity3))->mFloat = 100.0f;

			sector1->AdoptEntity(*entity3);

			Assert::AreEqual(static_cast<EntityFoo*>(sector1->Entities().Get<Scope*>(2))->mInt, 10);
			Assert::AreEqual(static_cast<EntityFoo*>(sector1->Entities().Get<Scope*>(2))->mFloat, 100.0f);
		}

		TEST_METHOD(Entity_Sector_GetWorld)
		{
			World world("world");

			Sector* sector1 = world.CreateSector("sector1");
			Assert::IsTrue(sector1->GetWorld() == &world);
		}

		TEST_METHOD(Entity_NameMethods)
		{
			World world("world");
			EntityFooFactory entityFooFactory;

			Sector* sector1 = world.CreateSector("sector1");
			Entity* entity1 = sector1->CreateEntity("EntityFoo", "entity1");

			//Name()
			Assert::IsTrue(entity1->Name() == "entity1");
			Assert::IsTrue(entity1->Append("name").Get<std::string>() == "entity1");
			
			//SetName()
			entity1->SetName("newName1");
			Assert::IsTrue(entity1->Name() == "newName1");
		}
		
		TEST_METHOD(Entity_GetSector)
		{
			World world("world");
			EntityFooFactory entityFooFactory;

			Sector* sector1 = world.CreateSector("sector1");
			Entity* entity1 = sector1->CreateEntity("EntityFoo", "entity1");

			Assert::IsTrue(entity1->GetSector() == sector1);
		}

		TEST_METHOD(Entity_GameTime)
		{
			World world("world");
			WorldState worldState;
			EntityFooFactory entityFooFactory;

			Sector* sector1 = world.CreateSector("sector1");
			world.CreateSector("sector2");

			sector1->CreateEntity("EntityFoo", "entity1");

			// Testing game time.
			GameClock gameClock;
			for (std::uint32_t i = 0; i < 10; ++i)
			{
				world.Update(worldState);
				gameClock.UpdateGameTime(worldState.mGameTime);
				worldState.mGameTime;
			}
		}

		TEST_METHOD(Entity_RTTI)
		{
			// Entity
			RTTI* entity = new Entity;

			Assert::IsTrue(entity->Is("Entity"));
			Assert::IsFalse(entity->Is("Foo"));
			Assert::IsTrue(entity->Is(Entity::TypeIdClass()));
			Assert::IsFalse(entity->Is(Foo::TypeIdClass()));
			Assert::IsNotNull(entity->As<Entity>());
			Assert::IsNull(entity->As<Foo>());
			Assert::IsNotNull(entity->QueryInterface(Entity::TypeIdClass()));
			Assert::IsNull(entity->QueryInterface(Foo::TypeIdClass()));
			delete entity;

			// Sector
			RTTI* sector = new Sector;

			Assert::IsTrue(sector->Is("Sector"));
			Assert::IsFalse(sector->Is("Foo"));
			Assert::IsTrue(sector->Is(Sector::TypeIdClass()));
			Assert::IsFalse(sector->Is(Foo::TypeIdClass()));
			Assert::IsNotNull(sector->As<Sector>());
			Assert::IsNull(sector->As<Foo>());
			Assert::IsNotNull(sector->QueryInterface(Sector::TypeIdClass()));
			Assert::IsNull(sector->QueryInterface(Foo::TypeIdClass()));
			delete sector;

			//World
			RTTI* world = new World("World");

			Assert::IsTrue(world->Is("World"));
			Assert::IsFalse(world->Is("Foo"));
			Assert::IsTrue(world->Is(World::TypeIdClass()));
			Assert::IsFalse(world->Is(Foo::TypeIdClass()));
			Assert::IsNotNull(world->As<World>());
			Assert::IsNull(world->As<Foo>());
			Assert::IsNotNull(world->QueryInterface(World::TypeIdClass()));
			Assert::IsNull(world->QueryInterface(Foo::TypeIdClass()));
			delete world;

			// EntityFoo
			RTTI* entityFoo = new EntityFoo;

			Assert::IsTrue(entityFoo->Is("EntityFoo"));
			Assert::IsFalse(entityFoo->Is("Foo"));
			Assert::IsTrue(entityFoo->Is(EntityFoo::TypeIdClass()));
			Assert::IsFalse(entityFoo->Is(Foo::TypeIdClass()));
			Assert::IsNotNull(entityFoo->As<EntityFoo>());
			Assert::IsNull(entityFoo->As<Foo>());
			Assert::IsNotNull(entityFoo->QueryInterface(EntityFoo::TypeIdClass()));
			Assert::IsNull(entityFoo->QueryInterface(Foo::TypeIdClass()));
			delete entityFoo;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityTest::sStartMemState;
};