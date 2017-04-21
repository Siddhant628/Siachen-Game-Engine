#pragma once
#include "Event.h"
#include "Vector.h"

#include <mutex>


namespace SiachenGameEngine
{
	namespace Events
	{
		template <typename PayloadT>
		Containers::Vector<EventSubscriber*> Event<PayloadT>::mSubscribers;

		template<typename PayloadT>
		Event<PayloadT>::Event(Event&& rhs) : EventPublisher(std::move(rhs)), mMessage(std::move(rhs.mMessage))
		{

		}

		template<typename PayloadT>
		Event<PayloadT>& Event<PayloadT>::operator=(Event&& rhs)
		{
			if (this != &rhs)
			{
				EventPublisher::operator=(std::move(rhs));
				mMessage = std::move(rhs.mMessage);
			}
			return *this;
		}

		template <typename PayloadT>
		Event<PayloadT>::Event(const PayloadT& messageObject, bool deleteAfterPublishing) : EventPublisher(mSubscribers, deleteAfterPublishing, mMutex), mMessage(messageObject)
		{

		}

		template<typename PayloadT>
		void Event<PayloadT>::Subscribe(EventSubscriber& subscriber)
		{
			std::lock_guard<std::mutex> lck(mMutex);
			mSubscribers.PushBack(&subscriber);
		}

		template<typename PayloadT>
		void Event<PayloadT>::Unsubscribe(EventSubscriber& unsubscriber)
		{
			std::lock_guard<std::mutex> lck(mMutex);
			mSubscribers.Remove(&unsubscriber);
		}

		template<typename PayloadT>
		void Event<PayloadT>::UnsubscribeAll()
		{
			std::lock_guard<std::mutex> lck(mMutex);
			mSubscribers.ClearAndFree();
		}

		template<typename PayloadT>
		const PayloadT& Event<PayloadT>::Message() const
		{
			return mMessage;
		}

		template <typename PayloadT>
		std::mutex Event<PayloadT>::mMutex;

		template <typename PayloadT>
		RTTI_DEFINITIONS(Event<PayloadT>)
	}
}