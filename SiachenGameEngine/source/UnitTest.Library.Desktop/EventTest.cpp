#include "pch.h"
#include "CppUnitTest.h"

#include "Event.h"
#include "EventQueue.h"

#include "Foo.h"
#include "FooSubscriber.h"

#include "GameTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Events;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::Library;
using namespace SiachenGameEngine::GameplayFramework;

using namespace std::chrono;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTest)
	{
	public:

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

		TEST_METHOD(Event_UnsubscribeAll)
		{
			Foo foo(10);
			FooSubscriber fooSub1, fooSub2;

			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Event<Foo> event(foo, false);
			// Delivering after subscribing
			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);
			event.Deliver();
			Assert::AreEqual(10, fooSub1.mInteger);
			Assert::AreEqual(10, fooSub2.mInteger);
			
			Event<Foo>::UnsubscribeAll();
			// Delivering after unsubscribing all
			fooSub1.mInteger = 0;
			fooSub2.mInteger = 0;
			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);
			event.Deliver();
			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);
		}

		TEST_METHOD(Event_Subscribe_Unsubscribe)
		{
			Foo foo(10);
			FooSubscriber fooSub1, fooSub2;
			Event<Foo> event(foo, false);
			// Subscribe
			Event<Foo>::Subscribe(fooSub1);
			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);
			event.Deliver();
			Assert::AreEqual(10, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);
			fooSub1.mInteger = 0;
			// Unsubscribe
			Event<Foo>::Unsubscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);
			event.Deliver();
			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(10, fooSub2.mInteger);
			fooSub2.mInteger = 0;

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Event_Message)
		{
			Foo foo(10);
			FooSubscriber fooSub1, fooSub2;
			Event<Foo> event(foo, false);

			Assert::IsTrue(event.Message() == foo);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventPublisher_Time)
		{
			GameTime time;
			time.SetCurrentTime(std::chrono::steady_clock::now());

			high_resolution_clock::time_point timePoint = time.CurrentTime();
			milliseconds delayDuration = milliseconds(1000);

			Foo foo(10);
			FooSubscriber fooSub1, fooSub2;
			Event<Foo> event(foo, false);

			Assert::IsTrue(event.TimeEnqueued() != timePoint);
			Assert::IsTrue(event.Delay() == milliseconds(0));
			event.SetTime(timePoint, delayDuration);
			Assert::IsTrue(event.TimeEnqueued() == timePoint);
			Assert::IsTrue(event.Delay() == delayDuration);
			
			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventPublisher_IsExpired)
		{
			GameTime time;
			time.SetCurrentTime(std::chrono::steady_clock::now());
			high_resolution_clock::time_point timePoint = time.CurrentTime();
			milliseconds delayDuration = milliseconds(1000);

			Foo foo(10);
			FooSubscriber fooSub1, fooSub2;

			Event<Foo> event(foo, false);
			event.SetTime(timePoint, delayDuration);
			
			Assert::IsFalse(event.IsExpired(timePoint));
			timePoint = timePoint + milliseconds(2000);
			Assert::IsTrue(event.IsExpired(timePoint));

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventPublisher_DeleteAfterPublishing)
		{
			Foo foo(10);
			
			Event<Foo> event(foo, false);
			Assert::IsFalse(event.DeleteAfterPublishing());

			Event<Foo>* event2 = new Event<Foo>(foo, true);
			Assert::IsTrue(event2->DeleteAfterPublishing());

			delete event2;
		}

		TEST_METHOD(EventQueue_Empty)
		{
			FooSubscriber fooSub1, fooSub2;
			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Foo foo1(1);
			Event<Foo> event1(foo1, false);

			EventQueue queue;
			GameTime gameTime;

			Assert::IsTrue(queue.IsEmpty());
			queue.Enqueue(event1, gameTime, milliseconds(1000));
			Assert::IsTrue(event1.Delay() == milliseconds(1000));
			Assert::IsFalse(queue.IsEmpty());

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventQueue_Size)
		{
			FooSubscriber fooSub1, fooSub2;
			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Foo foo1(1);
			Event<Foo> event1(foo1, false);

			EventQueue queue;
			GameTime gameTime;

			Assert::IsTrue(queue.Size() == 0U);
			queue.Enqueue(event1, gameTime, milliseconds(1000));
			Assert::IsTrue(queue.Size() == 1U);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventQueue_Send)
		{
			FooSubscriber fooSub1, fooSub2;
			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Foo foo1(1);
			Event<Foo> event1(foo1, false);

			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);

			EventQueue queue;
			queue.Send(event1);

			Assert::AreEqual(1, fooSub1.mInteger);
			Assert::AreEqual(1, fooSub2.mInteger);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventQueue_Clear)
		{
			FooSubscriber fooSub1, fooSub2;
			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Foo foo1(1);
			Event<Foo> event1(foo1, false);
			Foo foo2(2);
			Event<Foo>* event2 = new Event<Foo>(foo2, true);

			GameTime gameTime;
			EventQueue queue;
			queue.Enqueue(event1, gameTime, milliseconds(1000));
			queue.Enqueue(*event2, gameTime, milliseconds(1000));

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventQueue_Update)
		{
			FooSubscriber fooSub1, fooSub2;
			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Foo foo1(1);
			Event<Foo>* event1 = new Event<Foo>(foo1, true);
			Foo foo2(2);
			Event<Foo> event2(foo2, false);

			GameTime gameTime;
			EventQueue queue;

			queue.Enqueue(*event1, gameTime, milliseconds(1000));
			queue.Enqueue(event2, gameTime, milliseconds(2000));
			
			Assert::AreEqual(queue.Size(), 2U);
			queue.Update(gameTime);
			Assert::AreEqual(0, fooSub1.mInteger);
			Assert::AreEqual(0, fooSub2.mInteger);
			
			gameTime.SetCurrentTime(gameTime.CurrentTime() + milliseconds(1000));
			queue.Update(gameTime);
			Assert::AreEqual(queue.Size(), 1U);
			Assert::AreEqual(1, fooSub1.mInteger);
			Assert::AreEqual(1, fooSub2.mInteger);

			gameTime.SetCurrentTime(gameTime.CurrentTime() + milliseconds(1000));
			queue.Update(gameTime);
			Assert::AreEqual(queue.Size(), 0U);
			Assert::AreEqual(2, fooSub1.mInteger);
			Assert::AreEqual(2, fooSub2.mInteger);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Event_MoveSemantics)
		{
			FooSubscriber fooSub1, fooSub2;
			Event<Foo>::Subscribe(fooSub1);
			Event<Foo>::Subscribe(fooSub2);

			Foo foo1(1), foo2(2);
			Event<Foo> event1(foo1, false);
			Event<Foo> event2(foo2, false);
			
			EventQueue queue;

			// Move constructor
			Event<Foo> event3 = std::move(event1);
			
			queue.Send(event3);
			Assert::IsTrue(fooSub1.mInteger == 1);

			// Move assignment
			Event<Foo> event4(foo1, false);
			event4 = std::move(event2);
			
			queue.Send(event4);
			Assert::IsTrue(fooSub1.mInteger == 2);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Event_RTTI)
		{
			Foo foo1(1);
			RTTI* event1 = new Event<Foo>(foo1, false);
			RTTI* event2 = new Event<int>(1, false);

			Assert::IsTrue(event1->Is(Event<Foo>::TypeIdClass()));
			Assert::IsFalse(event2->Is(Event<Foo>::TypeIdClass()));
			
			Assert::IsTrue(event1->Is("Event"));
			Assert::IsFalse(foo1.Is("Event"));

			Assert::IsNotNull(event1->As<Event<Foo>>());
			Assert::IsNull(event2->As<Event<Foo>>());

			Assert::IsNotNull(event1->QueryInterface(Event<Foo>::TypeIdClass()));
			Assert::IsNull(event2->QueryInterface(Event<Foo>::TypeIdClass()));

			delete event1;
			delete event2;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
};