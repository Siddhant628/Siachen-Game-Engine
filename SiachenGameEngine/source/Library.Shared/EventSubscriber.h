#pragma once

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class EventPublisher;
		/**
		* An abstract base class for event subscribers.
		*/
		class EventSubscriber
		{
		public:
			virtual void Notify(const EventPublisher& eventObject) = 0;
			virtual ~EventSubscriber() = default;
		};
	}
}