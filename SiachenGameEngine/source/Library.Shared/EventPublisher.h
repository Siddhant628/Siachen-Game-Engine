#pragma once

#include "RTTI.h"
#include "Vector.h"
#include "EventSubscriber.h"

#include <chrono>

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/**
		* An abstract base class for concrete events.
		*/
		class EventPublisher : public RTTI
		{
			RTTI_DECLARATIONS(EventPublisher, RTTI)
		private:
			typedef std::chrono::high_resolution_clock::time_point TimePoint;
			typedef std::chrono::duration<std::int64_t, std::milli> MillisecondsDuration;
			// TODO Check default constructed values
			/**
			* The time at which this event was enqueued.
			*/
			TimePoint mTimeEnqueued;
			// TODO Check default constructed values
			// TODO Comment

			/**
			* The time after being enqueued after which this event would expire.
			*/
			MillisecondsDuration mDelay;
			/**
			* Whether the event should be deleted once it is published.
			*/
			bool mDeleteOnPublish;

		public:
			/**
			* Constructor.
			* @param subscribers A list of subscribers for this event.
			* @param deleteAfterPublish Set to true in order to delete the event object once the event has been published.
			*/
			EventPublisher(const Containers::Vector<EventSubscriber*>& subscribers, bool deleteAfterPublish);
			/**
			* Destructor.
			*/
			virtual ~EventPublisher() = default;
			// TODO Copy and move semantics
			// TODO Comment
			void SetTime(const TimePoint& enqueueTime, const MillisecondsDuration& delay = std::chrono::milliseconds(0));
			/**
			* Get the time when this event was enqueued.
			* @return The time point at which this event was enqueued.
			*/
			const TimePoint& TimeEnqueued() const;
			/**
			* Get the amount of time after being enqueued that this event would expire.
			* @return The time after which the event will expire.
			*/
			const MillisecondsDuration& Delay() const;
			/**
			* Check whether the event has expired.
			* @param currentTime The current time at which the expiration has to be checked for.
			* @return True if the current time is more than the time at which the event was enqueued, plus the delay.
			*/
			bool IsExpired(const TimePoint& currentTime) const;
			/**
			* Notify all the subscribers about the event.
			*/
			void Deliver();
			/**
			* Get whether the event should be deleted after publishing.
			* @return True if the event should be deleted after publishing.
			*/
			bool DeleteAfterPublishing() const;
		};
	}
}