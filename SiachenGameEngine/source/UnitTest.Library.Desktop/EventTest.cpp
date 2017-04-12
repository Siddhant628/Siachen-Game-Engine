#include "pch.h"
#include "CppUnitTest.h"

#include "Event.h"

#include "Foo.h"
#include "FooSubscriber.h"

#include "GameTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Events;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::Library;
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

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
};