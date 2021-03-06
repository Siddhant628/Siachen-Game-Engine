#pragma once
#include "EventPublisher.h"
#include "Vector.h"
#include "GameTime.h"

#include <mutex>

namespace SiachenGameEngine
{
	namespace Events
	{
		class EventQueue
		{
		private:
			typedef std::chrono::milliseconds MillisecondsDuration;
			/**
			* The actual queue of events which have to be serviced.
			*/
			Containers::Vector<EventPublisher*> mQueue;
			/**
			* A mutex to lock the queue of subscribers.
			*/
			mutable std::mutex mMutex;
			/**
			* A vector of events which need to be removed from the heap.
			*/
			Containers::Vector<EventPublisher*> mDeleteQueue;
			/**
			* 
			*/
			void ClearEventDeleteQueue();
		public:
			/**
			* Constructor.
			*/
			EventQueue() = default;
			/**
			* Destructor.
			*/
			~EventQueue();
			/**
			* Removed copy semantics.
			*/
			EventQueue(const EventQueue& rhs) = delete;
			EventQueue& operator=(const EventQueue& rhs) = delete;
			/**
			* Enqueue an event which has to be handled.
			* @param publisher The actual event object which has to be delivered.
			* @param gameTime A game time object which is used to retrieve the current time.
			* @param delay The optional delay after which the event should be delivered.
			*/
			void Enqueue(EventPublisher& publisher, const Library::GameTime& gameTime, const MillisecondsDuration& delay = std::chrono::milliseconds(0));
			/**
			* Send an event immediately.
			* @param The event object which has to be delivered.
			*/
			void Send(const EventPublisher& publisher) const;
			/**
			* Publish any queued events which have expired.
			* @param gameTime The game time object which is used to check which events have expired.
			*/
			void Update(const Library::GameTime& gameTime);
			/**
			* Clear the event queue.
			*/
			void Clear();
			/**
			* Check whether the event queue is empty.
			* @return True if the event queue is empty.
			*/
			bool IsEmpty() const;
			/**
			* Get the number of events in the event queue.
			* @return The number of events in the queue as an unsigned integer.
			*/
			std::uint32_t Size() const;
		};
	}
}