#pragma once

namespace SiachenGameEngine
{
	namespace Events
	{
		class EventPublisher;
		/**
		* An abstract base class for event subscribers.
		*/
		class EventSubscriber
		{
		public:
			virtual ~EventSubscriber() = default;
			/**
			* The receiver of the event which takes the event object as a parameter.
			*/
			virtual void Notify(const EventPublisher& eventObject) = 0;
		};
	}
}