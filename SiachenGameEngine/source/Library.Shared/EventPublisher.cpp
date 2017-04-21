#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

#include "Vector.h"
#include "assert.h"

#include <mutex>
#include <vector>
#include <future>

using namespace SiachenGameEngine::Containers;
using namespace std::chrono;

namespace SiachenGameEngine
{
	namespace Events
	{
		EventPublisher::EventPublisher(const Vector<EventSubscriber*>& subscribers, bool deleteAfterPublish, std::mutex& mutex) : mDeleteOnPublish(deleteAfterPublish), mSubscribers(&subscribers), mDelay(std::chrono::milliseconds(0)), mMutex(&mutex)
		{

		}

		EventPublisher::EventPublisher(EventPublisher&& rhs) : mTimeEnqueued(std::move(rhs.mTimeEnqueued)), mDelay(std::move(rhs.mDelay)), mSubscribers(rhs.mSubscribers), mDeleteOnPublish(rhs.mDeleteOnPublish), mMutex(rhs.mMutex)
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
				mMutex = rhs.mMutex;
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
			assert(mMutex != nullptr);
			// Create a copy of subscriber list in critical section
			Vector<EventSubscriber*>::Iterator it, end;
			Vector<EventSubscriber*> copySubscribers;

			{
				std::lock_guard<std::mutex> lck(*mMutex);
				copySubscribers = *mSubscribers;
			}
			// Iterate over the copy and deliver the event asynchronously
			it = copySubscribers.begin();
			end = copySubscribers.end();
			std::vector<std::future<void>> futures;

			for (; it != end; ++it)
			{
				futures.emplace_back(std::async(std::launch::async, [this, it]()
				{
					(*it)->Notify(*this);
				}));
			}
			std::for_each(futures.begin(), futures.end(), [](std::future<void>& fut)
			{
				// TODO Switch to get when handling exceptions
				fut.wait();
			});
		}

		const bool EventPublisher::DeleteAfterPublishing() const
		{
			return mDeleteOnPublish;
		}

		RTTI_DEFINITIONS(EventPublisher)
	}
}