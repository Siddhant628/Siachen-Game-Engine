#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "EventQueue.h"
#include "GameTime.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class QueueClearSubscriber : public Events::EventSubscriber
		{
		private:
			Events::EventQueue* mEventQueue;
		public:
			std::int32_t mInteger;

			QueueClearSubscriber(Events::EventQueue& eventQueue);
			~QueueClearSubscriber() = default;

			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}