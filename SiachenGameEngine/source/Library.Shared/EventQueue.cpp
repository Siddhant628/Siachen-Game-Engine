#include "pch.h"
#include "EventQueue.h"
#include "Vector.h"

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

			for (; it != end; ++it)
			{
				EventPublisher* publisher = (*it);
				if (publisher->IsExpired(gameTime.CurrentTime()))
				{
					publisher->Deliver();
				}
			}
		}

		void EventQueue::Clear()
		{

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