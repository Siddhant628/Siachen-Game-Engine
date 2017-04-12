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
		EventPublisher::EventPublisher(const Vector<EventSubscriber*>& subscribers, bool deleteAfterPublish) : mDeleteOnPublish(deleteAfterPublish), mSubscribers(&subscribers), mDelay(std::chrono::milliseconds(0))
		{

		}

		EventPublisher::EventPublisher(EventPublisher&& rhs) : mTimeEnqueued(std::move(rhs.mTimeEnqueued)), mDelay(std::move(rhs.mDelay)), mSubscribers(rhs.mSubscribers), mDeleteOnPublish(rhs.mDeleteOnPublish)
		{
			rhs.mSubscribers = nullptr;
		}

		EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
		{
			if (this != &rhs)
			{
				mTimeEnqueued = std::move(rhs.mTimeEnqueued);
				mDelay = std::move(rhs.mDelay);
				mSubscribers = rhs.mSubscribers;
				mDeleteOnPublish = rhs.mDeleteOnPublish;
				rhs.mSubscribers = nullptr;
			}
			return *this;
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
			return (currentTime >= (mTimeEnqueued + mDelay));
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