#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class FooSubscriber : public Events::EventSubscriber
		{
		public:
			std::int32_t mInteger;
			
			FooSubscriber();
			~FooSubscriber() = default;
			
			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}