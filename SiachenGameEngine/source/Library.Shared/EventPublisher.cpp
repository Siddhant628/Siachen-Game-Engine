#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

#include "Vector.h"
#include "assert.h"

using namespace SiachenGameEngine::Containers;
using namespace std::chrono;

namespace SiachenGameEngine
{
	namespace Events
	{
		EventPublisher::EventPublisher(const Vector<EventSubscriber*>& subscribers, bool deleteAfterPublish) : mDeleteOnPublish(false), mSubscribers(nullptr)
		{
			mSubscribers = &subscribers;
			mDeleteOnPublish = deleteAfterPublish;
		}

		void EventPublisher::SetTime(const TimePoint& enqueueTime, const MillisecondsDuration& delay /**  = std::chrono::milliseconds(0) **/)
		{
			mTimeEnqueued = enqueueTime;
			mDelay = delay;
		}

		const high_resolution_clock::time_point& EventPublisher::TimeEnqueued() const
		{
			return mTimeEnqueued;
		}

		const std::chrono::milliseconds& EventPublisher::Delay() const
		{
			return mDelay;
		}

		bool EventPublisher::IsExpired(const TimePoint& currentTime) const
		{
			return (currentTime > (mTimeEnqueued + mDelay));
		}

		void EventPublisher::Deliver() const
		{
			assert(mSubscribers != nullptr);
			Vector<EventSubscriber*>::Iterator it = mSubscribers->begin();
			Vector<EventSubscriber*>::Iterator end = mSubscribers->end();
			for (; it != end; ++it)
			{
				(*it)->Notify(*this);
			}
		}

		const bool EventPublisher::DeleteAfterPublishing() const
		{
			return mDeleteOnPublish;
		}

		RTTI_DEFINITIONS(EventPublisher)
	}
}