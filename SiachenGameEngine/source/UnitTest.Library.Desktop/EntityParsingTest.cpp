#include "pch.h"
#include "CppUnitTest.h"

#include "XmlSharedDataWorld.h"
#include "XmlParseHelperWorld.h"
#include "XmlParseHelperWorldPrimitives.h"
#include "SampleXmlSharedData.h"

#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "EntityFoo.h"

#include "RTTI.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::GameplayFramework;
using namespace SiachenGameEngine::Containers;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EntityParsingTest)
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

		TEST_METHOD(EntityParsing_File)
		{
			XmlSharedDataWorld sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperWorld worldHelper;
			XmlParseHelperWorldPrimitives worldPrimitivesHelpers;
			parseMaster.AddHelper(worldHelper);
			parseMaster.AddHelper(worldPrimitivesHelpers);

			EntityFooFactory entityFooFactory;

			parseMaster.ParseFromFile("XmlWithWorld.xml");

			World* world = static_cast<World*>(sharedData.mCurrentScope);
			Assert::IsTrue(world->Name() == "World1");
			
			Datum& datum = world->Sectors();
			Assert::AreEqual(datum.Size(), 2U);

			Entity* entity1 = static_cast<Entity*>((static_cast<Sector*>(datum.Get<Scope*>()))->Entities().Get<Scope*>());
			Assert::AreEqual(static_cast<EntityFoo*>(entity1)->mFloat, 10.0f);
			Assert::AreEqual(entity1->Append("float").Get<std::float_t>(), 10.0f);
			Assert::AreEqual(static_cast<EntityFoo*>(entity1)->mInt, 20);
			Assert::AreEqual(entity1->Append("integer").Get<std::int32_t>(), 20);
			Assert::IsTrue(entity1->Name() == "entity1");

			Entity* entity2 = static_cast<Entity*>((static_cast<Sector*>(datum.Get<Scope*>(1)))->Entities().Get<Scope*>());
			Assert::AreEqual(static_cast<EntityFoo*>(entity2)->mInt, 30);
			Assert::AreEqual(entity2->Append("integer").Get<std::int32_t>(), 30);
			Assert::IsTrue(entity2->Name() == "entity2");

			// Testing for a newly inserted integer
			Assert::AreEqual(entity2->Append("InternalInteger").Get<std::int32_t>(), 40);

			Assert::IsTrue(static_cast<Sector*>(datum.Get<Scope*>())->Name() == "Sector1");
			Assert::IsTrue(static_cast<Sector*>(datum.Get<Scope*>(1))->Name() == "Sector2");

			Assert::AreEqual(entity2->Append("float").Get<std::float_t>(), 40.0f);
			Assert::AreEqual(entity2->Append("InternalFloat").Get<std::float_t>(), 50.0f);

			// Testing for strings
			Entity* entity3 = static_cast<Entity*>((static_cast<Sector*>(datum.Get<Scope*>(1)))->Entities().Get<Scope*>(1));
			Assert::IsTrue(static_cast<EntityFoo*>(entity3)->mString == "changed");
			Assert::IsTrue(entity3->Append("InternalString").Get<std::string>() == "additional");
			Assert::IsTrue(entity3->Name() == "entity3");
		}

		TEST_METHOD(EntityParsing_FileClone)
		{
			XmlSharedDataWorld sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperWorld worldHelper;
			XmlParseHelperWorldPrimitives worldPrimitivesHelpers;
			parseMaster.AddHelper(worldHelper);
			parseMaster.AddHelper(worldPrimitivesHelpers);

			EntityFooFactory entityFooFactory;

			XmlParseMaster* clonedParseMaster = parseMaster.Clone();
			clonedParseMaster->ParseFromFile("XmlWithWorld.xml");

			World* world = static_cast<World*>(static_cast<XmlSharedDataWorld*>(clonedParseMaster->GetSharedData())->mCurrentScope);
			Assert::IsTrue(world->Name() == "World1");

			Datum& datum = world->Sectors();
			Assert::AreEqual(datum.Size(), 2U);

			Entity* entity1 = static_cast<Entity*>((static_cast<Sector*>(datum.Get<Scope*>()))->Entities().Get<Scope*>());
			Assert::AreEqual(static_cast<EntityFoo*>(entity1)->mFloat, 10.0f);
			Assert::AreEqual(entity1->Append("float").Get<std::float_t>(), 10.0f);
			Assert::AreEqual(static_cast<EntityFoo*>(entity1)->mInt, 20);
			Assert::AreEqual(entity1->Append("integer").Get<std::int32_t>(), 20);
			Assert::IsTrue(entity1->Name() == "entity1");

			Entity* entity2 = static_cast<Entity*>((static_cast<Sector*>(datum.Get<Scope*>(1)))->Entities().Get<Scope*>());
			Assert::AreEqual(static_cast<EntityFoo*>(entity2)->mInt, 30);
			Assert::AreEqual(entity2->Append("integer").Get<std::int32_t>(), 30);
			Assert::IsTrue(entity2->Name() == "entity2");

			Assert::IsTrue(static_cast<Sector*>(datum.Get<Scope*>())->Name() == "Sector1");
			Assert::IsTrue(static_cast<Sector*>(datum.Get<Scope*>(1))->Name() == "Sector2");

			// Testing for strings
			Entity* entity3 = static_cast<Entity*>((static_cast<Sector*>(datum.Get<Scope*>(1)))->Entities().Get<Scope*>(1));
			Assert::IsTrue(static_cast<EntityFoo*>(entity3)->mString == "changed");
			Assert::IsTrue(entity3->Append("InternalString").Get<std::string>() == "additional");
			Assert::IsTrue(entity3->Name() == "entity3");

			delete clonedParseMaster;
		}

		TEST_METHOD(EntityParsing_RTTI)
		{
			RTTI* sharedData = new XmlSharedDataWorld;

			Assert::IsTrue(sharedData->Is("XmlSharedDataWorld"));
			Assert::IsFalse(sharedData->Is("EntityFoo"));
			Assert::IsTrue(sharedData->Is(XmlSharedDataWorld::TypeIdClass()));
			Assert::IsFalse(sharedData->Is(EntityFoo::TypeIdClass()));
			Assert::IsNotNull(sharedData->As<XmlSharedDataWorld>());
			Assert::IsNull(sharedData->As<EntityFoo>());
			Assert::IsNotNull(sharedData->QueryInterface(XmlSharedDataWorld::TypeIdClass()));
			Assert::IsNull(sharedData->QueryInterface(EntityFoo::TypeIdClass()));
			delete sharedData;
		}

		TEST_METHOD(EntityParsing_Helpers)
		{
			SampleXmlSharedData sharedData;

			XmlParseHelperWorld worldHelper;
			XmlParseHelperWorldPrimitives worldPrimitivesHelpers;

			auto expression1 = [&worldHelper, &sharedData] {worldHelper.Initialize(sharedData); };
			Assert::ExpectException<std::runtime_error>(expression1);


			auto expression2 = [&worldPrimitivesHelpers, &sharedData] {worldPrimitivesHelpers.Initialize(sharedData); };
			Assert::ExpectException<std::runtime_error>(expression2);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityParsingTest::sStartMemState;
};