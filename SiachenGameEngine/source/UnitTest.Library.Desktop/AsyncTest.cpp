#include "pch.h"
#include "CppUnitTest.h"

#include "Event.h"
#include "EventQueue.h"

#include "Foo.h"

#include "FooSubscriber.h"
#include "UnsubscriberSubscriber.h"
#include "SubscriberSubscriber.h"
#include "UnsubscribeAllSubscriber.h"

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

		TEST_METHOD(Async_Deliver_UnsubscriberSubscriber)
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

		TEST_METHOD(Async_Deliver_SubscriberSubscriber)
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

		TEST_METHOD(Async_Deliver_UnsubscribeAllSubscriber)
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
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AsyncTest::sStartMemState;
};