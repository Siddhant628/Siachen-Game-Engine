#pragma once
#include "EventPublisher.h"

#include <mutex>

namespace SiachenGameEngine
{
	namespace Events
	{
		template <typename PayloadT>
		class Event final : public EventPublisher
		{
			RTTI_DECLARATIONS(Event, EventPublisher)
		private:
			static Containers::Vector<EventSubscriber*> mSubscribers;
			/**
			* A pointer to the actual message object.
			*/
			PayloadT mMessage;
			/**
			* Mutex to lock the subscriber list for processing.
			*/
			static std::mutex mMutex;
		public:
			/**
			* Copy constructor.
			*/
			Event(const Event& rhs) = default;
			/**
			* Move constructor.
			*/
			Event(Event&& rhs);
			Event& operator=(Event&& rhs);

			/**
			* Constructor.
			* @param messageObject A reference to the message object.
			* @param deleteAfterPublishing A boolean indicating whether to delete the event object after it is published.
			*/
			Event(const PayloadT& messageObject, bool deleteAfterPublishing);
			/**
			* Destructor.
			*/
			~Event() = default;
			/**
			* Add a subscriber to the list of subscribers.
			* @param subscriber A reference to the subscriber object which has to be added to the list.
			*/
			static void Subscribe(EventSubscriber& subscriber);
			/**
			* Remove a subscriber from the list of subscribers.
			* @param unsubscriber A reference to the subscriber object which has to be removed from the list.
			*/
			static void Unsubscribe(EventSubscriber& unsubscriber);
			/**
			* Unsubscribe all subscribers to this event.
			*/
			static void UnsubscribeAll();
			/**
			* Get the message object.
			*/
			const PayloadT& Message() const;
		};
	}
}

#include "Event.inl"