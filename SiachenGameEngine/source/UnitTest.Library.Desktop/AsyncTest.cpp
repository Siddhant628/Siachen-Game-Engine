#include "pch.h"
#include "CppUnitTest.h"

#include "Event.h"
#include "EventQueue.h"

#include "Foo.h"

#include "FooSubscriber.h"
#include "UnsubscriberSubscriber.h"
#include "SubscriberSubscriber.h"
#include "UnsubscribeAllSubscriber.h"
#include "EnqueueSubscriber.h"
#include "QueueClearSubscriber.h"

#include "GameTime.h"

#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace SiachenGameEngine::Events;
using namespace SiachenGameEngine::HelperClasses;
using namespace SiachenGameEngine::Library;
using namespace SiachenGameEngine::GameplayFramework;
using namespace std;

using namespace std::chrono;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AsyncTest)
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

		TEST_METHOD(Async_Event_Deliver_UnsubscriberSubscriber)
		{
			FooSubscriber fooSubs[700];
			UnsubscriberSubscriber unSubs[350];
			
			for (int32_t i = 0; i < 350; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
				unSubs[i].mInteger = i;
				Event<Foo>::Subscribe(unSubs[i]);
			}
			for (int32_t i = 350; i < 700; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
			}

			Foo foo1(2000);
			Event<Foo> event1(foo1, false);
			event1.Deliver();

			for (int32_t i = 0; i < 350; ++i)
			{
				Assert::AreEqual(unSubs[i].mInteger, 2000);
			}
			for (int32_t i = 0; i < 700; ++i)
			{
				Assert::AreEqual(fooSubs[i].mInteger, 2000);
			}

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Async_Event_Deliver_SubscriberSubscriber)
		{
			FooSubscriber fooSubs[700];
			SubscriberSubscriber subSubs[350];
			
			for (int32_t i = 0; i < 350; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
				subSubs[i].mInteger = i;
				Event<Foo>::Subscribe(subSubs[i]);
			}
			for (int32_t i = 350; i < 700; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
			}

			Foo foo1(2000);
			Event<Foo> event1(foo1, false);
			event1.Deliver();

			for (int32_t i = 0; i < 350; ++i)
			{
				Assert::AreEqual(subSubs[i].mInteger, 2000);
			}
			for (int32_t i = 0; i < 700; ++i)
			{
				Assert::AreEqual(fooSubs[i].mInteger, 2000);
			}

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Async_Event_Deliver_UnsubscribeAllSubscriber)
		{
			FooSubscriber fooSubs[700];
			UnsubscribeAllSubscriber unSubAllSubs[350];
			
			for (int32_t i = 0; i < 350; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
				unSubAllSubs[i].mInteger = i;
				Event<Foo>::Subscribe(unSubAllSubs[i]);
			}
			for (int32_t i = 350; i < 700; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
			}

			Foo foo1(2000);
			Event<Foo> event1(foo1, false);
			event1.Deliver();

			for (int32_t i = 0; i < 350; ++i)
			{
				Assert::AreEqual(unSubAllSubs[i].mInteger, 2000);
			}
			for (int32_t i = 0; i < 700; ++i)
			{
				Assert::AreEqual(fooSubs[i].mInteger, 2000);
			}
		}

		TEST_METHOD(Async_Queue_Update_Enqueue)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			// Create subscribers
			FooSubscriber fooSubs[20];
			vector<EnqueueSubscriber*> enqueueSubs;
			for (int32_t i = 0; i < 20; ++i)
			{
				EnqueueSubscriber* subscriber = new EnqueueSubscriber(eventQueue, gameTime);
				subscriber->mInteger = i;
				enqueueSubs.push_back(subscriber);
			}
			// Subscribe the subscribers
			for (int32_t i = 0; i < 20; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
				enqueueSubs.at(i)->mInteger = i;
				Event<Foo>::Subscribe(*enqueueSubs.at(i));
			}
			// Create and enqueue events
			for (int32_t i = 0; i < 30; ++i)
			{
				eventQueue.Enqueue(*(new Event<Foo>(Foo(2000), true)), gameTime, std::chrono::milliseconds(0));
			}

			// Update and check affect on queued subscribers
			eventQueue.Update(gameTime);
			for (int32_t i = 0; i < 20; ++i)
			{
				Assert::AreEqual(enqueueSubs.at(i)->mInteger, 2000);
			}
			eventQueue.Update(gameTime);
			for (int32_t i = 0; i < 20; ++i)
			{
				Assert::AreEqual(enqueueSubs.at(i)->mInteger, 1000);
			}

			// Clear heap
			for_each(enqueueSubs.begin(), enqueueSubs.end(), [](EnqueueSubscriber* subscriber)
			{
				delete subscriber;
			});
			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Async_Queue_Update_Clear)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			// Create subscribers
			FooSubscriber fooSubs[300];
			vector<QueueClearSubscriber*> queueClearSubs;
			for (int32_t i = 0; i < 300; ++i)
			{
				QueueClearSubscriber* subscriber = new QueueClearSubscriber(eventQueue);
				subscriber->mInteger = i;
				queueClearSubs.push_back(subscriber);
			}
			// Subscribe the subscribers
			for (int32_t i = 0; i < 300; ++i)
			{
				fooSubs[i].mInteger = i;
				Event<Foo>::Subscribe(fooSubs[i]);
				queueClearSubs.at(i)->mInteger = i;
				Event<Foo>::Subscribe(*queueClearSubs.at(i));
			}
			// Create and enqueue events
			for (int32_t i = 0; i < 250; ++i)
			{
				eventQueue.Enqueue(*(new Event<Foo>(Foo(2000), true)), gameTime, std::chrono::milliseconds(0));
			}

			// Update and check affect on queued subscribers
			eventQueue.Update(gameTime);
			for (int32_t i = 0; i < 300; ++i)
			{
				Assert::AreEqual(queueClearSubs.at(i)->mInteger, 2000);
			}
			eventQueue.Update(gameTime);

			// Clear heap
			for_each(queueClearSubs.begin(), queueClearSubs.end(), [](QueueClearSubscriber* subscriber)
			{
				delete subscriber;
			});
			Event<Foo>::UnsubscribeAll();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AsyncTest::sStartMemState;
};