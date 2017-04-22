#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class UnsubscribeAllSubscriber : public Events::EventSubscriber
		{
		public:
			std::int32_t mInteger;

			UnsubscribeAllSubscriber();
			~UnsubscribeAllSubscriber() = default;

			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}