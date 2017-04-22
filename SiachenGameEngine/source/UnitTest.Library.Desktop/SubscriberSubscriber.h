#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "FooSubscriber.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class SubscriberSubscriber : public Events::EventSubscriber
		{
		private:
			FooSubscriber* fooSub;
		public:
			std::int32_t mInteger;

			SubscriberSubscriber();
			~SubscriberSubscriber();

			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}