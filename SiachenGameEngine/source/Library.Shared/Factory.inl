#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		template<typename AbstractFactoryT>
		Containers::HashMap<std::string, Factory<AbstractFactoryT>*> Factory<AbstractFactoryT>::mFactoryTable;

		template <typename AbstractProductT>
		Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& className)
		{
			Factory<AbstractProductT>* factoryToReturn = nullptr;
			if (mFactoryTable.ContainsKey(className))
			{
				factoryToReturn = mFactoryTable[className];
			}
			return factoryToReturn;
		}

		template<typename AbstractProductT>
		AbstractProductT* Factory<AbstractProductT>::Create(const std::string& className)
		{
			AbstractProductT* productToReturn = nullptr;
			if (mFactoryTable.ContainsKey(className))
			{
				productToReturn = mFactoryTable[className]->Create();
			}
			return productToReturn;
		}

		template<typename AbstractProductT>
		typename Containers::HashMap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::begin()
		{
			return mFactoryTable.begin();
		}

		template<typename AbstractProductT>
		typename Containers::HashMap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::end()
		{
			return mFactoryTable.end();
		}

		template<typename AbstractProductT>
		void Factory<AbstractProductT>::Add(Factory<AbstractProductT>& factoryToAdd)
		{
			mFactoryTable.Insert(make_pair(factoryToAdd.ClassName(), &factoryToAdd));
		}

		template<typename AbstractProductT>
		void Factory<AbstractProductT>::Remove(Factory<AbstractProductT>& factoryToRemove)
		{
			mFactoryTable.Remove(factoryToRemove.ClassName());
		}
	}
}