#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "EntityFoo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::HelperClasses;

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