#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "EventQueue.h"
#include "GameTime.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class EnqueueSubscriber : public Events::EventSubscriber
		{
		private:
			Events::EventQueue* mEventQueue;
			Library::GameTime* mGameTime;
		public:
			std::int32_t mInteger;

			EnqueueSubscriber(Events::EventQueue& eventQueue, Library::GameTime& gameTime);
			~EnqueueSubscriber() = default;

			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}