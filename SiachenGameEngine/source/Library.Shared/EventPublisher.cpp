#include "pch.h"
#include "EventPublisher.h"

using namespace SiachenGameEngine::Containers;
using namespace std::chrono;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		EventPublisher::EventPublisher(const Vector<EventSubscriber*>& subscribers, bool deleteAfterPublish)
		{
			subscribers;
			deleteAfterPublish;
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

		const std::chrono::duration<std::int64_t, std::milli>& EventPublisher::Delay() const
		{
			return mDelay;
		}

		bool EventPublisher::IsExpired(const TimePoint& currentTime) const
		{
			return (currentTime > (mTimeEnqueued + mDelay));
		}

		void EventPublisher::Deliver()
		{

		}

		bool EventPublisher::DeleteAfterPublishing() const
		{
			return mDeleteOnPublish;
		}

		RTTI_DEFINITIONS(EventPublisher)
	}
}