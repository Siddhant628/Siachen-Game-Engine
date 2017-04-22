#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class UnsubscriberSubscriber : public Events::EventSubscriber
		{
		public:
			std::int32_t mInteger;

			UnsubscriberSubscriber();
			~UnsubscriberSubscriber() = default;

			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}