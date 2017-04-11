#pragma once

#include "RTTI.h"
#include "Vector.h"
#include "EventSubscriber.h"

#include <chrono>

namespace SiachenGameEngine
{
	namespace Events
	{
		/**
		* An abstract base class for concrete events, it provides the necessary common interface for all the events.
		*/
		class EventPublisher : public GameplayFramework::RTTI
		{
			RTTI_DECLARATIONS(EventPublisher, GameplayFramework::RTTI)
		private:
			typedef std::chrono::high_resolution_clock::time_point TimePoint;
			typedef std::chrono::milliseconds MillisecondsDuration;
			
			// TODO Check default constructed values
			/**
			* The time at which this event was enqueued.
			*/
			TimePoint mTimeEnqueued;
			// TODO Check default constructed values
			/**
			* The time after being enqueued after which this event would expire.
			*/
			MillisecondsDuration mDelay;
			/**
			* Whether the event should be deleted once it is published.
			*/
			bool mDeleteOnPublish;
			/**
			* List of subscribers for this event.
			*/
			Containers::Vector<EventSubscriber*>* mSubscribers;

		public:
			// TODO Copy and move semantics

			/**
			* Constructor.
			* @param subscribers A list of subscribers for this event.
			* @param deleteAfterPublish Set to true in order to delete the event object once the event has been published.
			*/
			EventPublisher(Containers::Vector<EventSubscriber*>& subscribers, bool deleteAfterPublish);
			/**
			* Destructor.
			*/
			virtual ~EventPublisher() = default;
			
			/**
			* Set the time at which this event was enqueued. Also, optionally, set the delay after which it should be delivered.
			* @param enqueueTime The time at which the event was enqueued.
			* @param delay The time after being enqueued after which this event should expire.
			*/
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
			void Deliver() const;
			/**
			* Get whether the event should be deleted after publishing.
			* @return True if the event should be deleted after publishing.
			*/
			const bool DeleteAfterPublishing() const;
		};
	}
}