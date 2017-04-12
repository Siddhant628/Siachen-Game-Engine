#include "pch.h"
#include "EventQueue.h"
#include "Vector.h"

#include <algorithm>

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Events
	{
		void EventQueue::Enqueue(EventPublisher& publisher, const Library::GameTime& gameTime, const MillisecondsDuration& delay /** = std::chrono::milliseconds(0) **/)
		{
			publisher.SetTime(gameTime.CurrentTime(), delay);
			mQueue.PushBack(&publisher);
		}

		void EventQueue::Send(const EventPublisher& publisher) const
		{
			publisher.Deliver();
		}

		void EventQueue::Update(const Library::GameTime& gameTime)
		{
			Vector<EventPublisher*>::Iterator it = mQueue.begin();
			Vector<EventPublisher*>::Iterator end = mQueue.end();
			Vector<EventPublisher*>::Iterator expiredIt;

			expiredIt = std::partition(it, end, [&gameTime](EventPublisher* publisher) {return !publisher->IsExpired(gameTime.CurrentTime()); });

			for (it = expiredIt; it != end; ++it)
			{
				EventPublisher* publisher = *it;
				publisher->Deliver();
				if (publisher->DeleteAfterPublishing())
				{
					delete publisher;
				}
			}
			mQueue.Remove(expiredIt, end);
		}

		void EventQueue::Clear()
		{
			Vector<EventPublisher*>::Iterator it = mQueue.begin();
			Vector<EventPublisher*>::Iterator end = mQueue.end();

			for (; it != end; ++it)
			{
				EventPublisher* publisher = *it;
				if (publisher->DeleteAfterPublishing())
				{
					delete publisher;
				}
			}
			mQueue.ClearAndFree();
		}
		
		bool EventQueue::IsEmpty()
		{
			return mQueue.IsEmpty();
		}
		
		std::uint32_t EventQueue::Size() const
		{
			return mQueue.Size();
		}
	}
}