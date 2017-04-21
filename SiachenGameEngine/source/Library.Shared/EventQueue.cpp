#include "pch.h"
#include "EventQueue.h"
#include "Vector.h"

#include <algorithm>
#include <assert.h>
#include <vector>
#include <future>
#include <thread>

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Events
	{
		void EventQueue::ClearEventDeleteQueue()
		{
			Vector<EventPublisher*>::Iterator it = mDeleteQueue.begin();
			Vector<EventPublisher*>::Iterator end = mDeleteQueue.end();

			for (; it != end; ++it)
			{
				delete (*it);
			}
			mDeleteQueue.ClearAndFree();
		}

		EventQueue::~EventQueue()
		{
			Clear();
		}

		void EventQueue::Enqueue(EventPublisher& publisher, const Library::GameTime& gameTime, const MillisecondsDuration& delay /** = std::chrono::milliseconds(0) **/)
		{
			std::lock_guard<std::mutex> lck(mMutex);
			publisher.SetTime(gameTime.CurrentTime(), delay);
			mQueue.PushBack(&publisher);
		}

		void EventQueue::Send(const EventPublisher& publisher) const
		{
			publisher.Deliver();
		}

		void EventQueue::Update(const Library::GameTime& gameTime)
		{
			Vector<EventPublisher*>::Iterator it, end, expiredIt;
			Vector<EventPublisher*> queueCopy;
			EventPublisher* firstExpiredEvent = nullptr;
			// Critical section
			{
				std::lock_guard<std::mutex> lck(mMutex);
				// Partitioning of the event queue
				it = mQueue.begin();
				end = mQueue.end();
				expiredIt = std::partition(it, end, [&gameTime](EventPublisher* publisher) {return !publisher->IsExpired(gameTime.CurrentTime()); });
				// Copy the queue before releasing the lock
				queueCopy = mQueue;
				// Add the publishers which will have to be deleted to the delete queue, remove the expired events from queue
				for (it = expiredIt; it != end; ++it)
				{
					EventPublisher* publisher = *it;
					if (publisher->DeleteAfterPublishing())
					{
						mDeleteQueue.PushBack(publisher);
					}
				}
				if (expiredIt != end)
				{
					firstExpiredEvent = *expiredIt;
					mQueue.Remove(expiredIt, end);
				}
			}

			// Post critical section, deliver the events asynchronously
			std::vector<std::future<void>> futures;

			if (firstExpiredEvent)
			{
				Vector<EventPublisher*>::Iterator itCopy = queueCopy.Find(firstExpiredEvent);
				Vector<EventPublisher*>::Iterator endCopy = queueCopy.end();
				assert(itCopy != queueCopy.end());

				for (; itCopy != endCopy; ++itCopy)
				{
					futures.emplace_back(std::async(std::launch::async, [itCopy]()
					{
						(*itCopy)->Deliver();
					}));
				}

				std::for_each(futures.begin(), futures.end(), [](std::future<void>& fut)
				{
					fut.get();
				});
			}
			// Delete the events which were delivered but are still in the heap memory
			ClearEventDeleteQueue();
		}

		void EventQueue::Clear()
		{
			std::lock_guard<std::mutex> lck(mMutex);
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

		bool EventQueue::IsEmpty() const
		{
			std::lock_guard<std::mutex> lck(mMutex);
			return mQueue.IsEmpty();
		}

		std::uint32_t EventQueue::Size() const
		{
			std::lock_guard<std::mutex> lck(mMutex);
			return mQueue.Size();
		}
	}
}