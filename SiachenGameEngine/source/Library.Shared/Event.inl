#pragma once
#include "Event.h"

namespace SiachenGameEngine
{
	namespace Events
	{
		template <typename PayloadT>
		Event::Event(const PayloadT& messageObject, bool deleteAfterPublishing) : EventPublisher(mSubscribers, deleteAfterPublishing), mMessage(&messageObject)
		{

		}

		template<typename PayloadT>
		void Event<PayloadT>::Subscribe(EventSubscriber& subscriber)
		{
			mSubscribers.PushBack(&subscriber);
		}

		template<typename PayloadT>
		void Event<PayloadT>::Unsubscribe(EventSubscriber& unsubscriber)
		{
			mSubscribers.Remove(&unsubscriber);
		}

		template<typename PayloadT>
		void Event<PayloadT>::UnsubscribeAll()
		{
			mSubscribers.Clear();
		}

		template<typename PayloadT>
		const PayloadT& Event<PayloadT>::Message() const
		{
			return *mMessage;
		}
	}
}