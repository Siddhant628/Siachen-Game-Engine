#include "pch.h"
#include "FooSubscriber.h"
#include "Foo.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		FooSubscriber::FooSubscriber() : mInteger(0)
		{

		}

		void FooSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Foo* object = eventObject.As<Foo>();
			if (object)
			{
				mInteger = object->GetValue();
			}
		}
	}
}