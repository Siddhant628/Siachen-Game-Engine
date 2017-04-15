#include "pch.h"
#include "CppUnitTest.h"

#include "EventMessageAttributed.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"

#include "World.h"
#include "Event.h"

#include "RTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Events;
using namespace SiachenGameEngine::GameplayFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ReactionTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Reaction_Initialize)
		{
			World world("World");

			EventMessageAttributed message;
			ActionList action;
			ActionEvent aEvent;
			ReactionAttributed reaction;
			
			Event<EventMessageAttributed>::UnsubscribeAll();
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

		TEST_METHOD(EventMessageAttributed_Methods)
		{
			EventMessageAttributed message;

			// Get / Set Subtype
			message.SetSubtype("Butter");
			Assert::IsTrue(message.Append("subtype").Get<std::string>() == "Butter");
			Assert::IsTrue(message.GetSubtype() == "Butter");

			// Get / Set World
			auto worldExpression = [&message] {message.GetWorld(); };
			Assert::ExpectException<std::runtime_error>(worldExpression);

			World world("Chicken");
			message.SetWorld(world);
			Assert::IsTrue(&message.GetWorld() == &world);
		}

		TEST_METHOD(ReactionAttributed_Methods)
		{
			World world("World");
			WorldState state;
			world.Update(state);

			ReactionAttributed reaction;
			Assert::IsNotNull(reaction.Find("subtypes"));
			reaction.Append("subtypes").PushBack("Chicken");
			reaction.Append("subtypes").PushBack("Butter");

			EventMessageAttributed message;
			message.Append("auxInt").PushBack(1);
			message.Append("auxInt").PushBack(2);
			message.Append("auxStr").PushBack("str");
			
			message.SetSubtype("Butter");
			message.SetWorld(world);

			Assert::IsNull(reaction.Find("auxInt"));
			Assert::IsNull(reaction.Find("auxStr"));
			Event<EventMessageAttributed> event(message, false);
			event.Deliver();
			Assert::IsNotNull(reaction.Find("auxInt"));
			Assert::IsNotNull(reaction.Find("auxStr"));

			Assert::AreEqual(reaction.Append("auxInt").Get<std::int32_t>(), 1);
			Assert::AreEqual(reaction.Append("auxInt").Get<std::int32_t>(1), 2);

			Event<EventMessageAttributed>::UnsubscribeAll();
		}

		TEST_METHOD(ActionEvent_Methods)
		{
			ActionEventFactory aEventFactory;
			WorldState worldState;
			World world("World1");
			//world.Update(worldState);
			ReactionAttributed reaction;
			reaction.Append("subtypes").PushBack("Butter");
			
			ActionEvent* actionEvent = static_cast<ActionEvent*>(world.CreateAction("ActionEvent", "firstEvent"));
			
			Assert::IsNotNull(actionEvent->Find("subtype"));
			Assert::IsNotNull(actionEvent->Find("delay"));
			actionEvent->Append("subtype").Set("Butter");
			actionEvent->Append("delay").Set(2000);
			actionEvent->Append("AuxInt").PushBack(10);

			Assert::IsNull(reaction.Find("AuxInt"));
			world.Update(worldState);
			worldState.mGameTime.SetCurrentTime(worldState.mGameTime.CurrentTime() + std::chrono::milliseconds(2000));
			world.Update(worldState);
			Assert::IsNotNull(reaction.Find("AuxInt"));
			Assert::AreEqual(reaction.Append("AuxInt").Get<std::int32_t>(), 10);

			Event<EventMessageAttributed>::UnsubscribeAll();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionTest::sStartMemState;
};