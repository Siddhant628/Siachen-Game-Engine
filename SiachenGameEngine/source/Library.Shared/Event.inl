#pragma once
#include "Event.h"
#include "Vector.h"


namespace SiachenGameEngine
{
	namespace Events
	{
		template <typename PayloadT>
		Containers::Vector<EventSubscriber*> Event<PayloadT>::mSubscribers;

		template <typename PayloadT>
		Event<PayloadT>::Event(const PayloadT& messageObject, bool deleteAfterPublishing) : EventPublisher(mSubscribers, deleteAfterPublishing), mMessage(messageObject)
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
			mSubscribers.ClearAndFree();
		}

		template<typename PayloadT>
		const PayloadT& Event<PayloadT>::Message() const
		{
			return mMessage;
		}

		template <typename PayloadT>
		RTTI_DEFINITIONS(Event<PayloadT>)
	}
}