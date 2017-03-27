#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		template <typename AbstractProductT>
		Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& className)
		{
			className;
			return nullptr;
		}

		template<typename AbstractProductT>
		AbstractProductT* Factory<AbstractProductT>::Create(const std::string& className)
		{
			className;
			return nullptr;
		}

		template<typename AbstractProductT>
		void Factory<AbstractProductT>::Add(Factory<AbstractProductT>& factoryToAdd)
		{
			factoryToAdd;
		}

		template<typename AbstractProductT>
		void Factory<AbstractProductT>::Remove(Factory<AbstractProductT>& factoryToRemove)
		{
			factoryToRemove;
		}
	}
}