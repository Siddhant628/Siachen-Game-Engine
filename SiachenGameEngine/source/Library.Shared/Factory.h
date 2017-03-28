#pragma once
#include "HashMap.h"
#include "assert.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		template <typename AbstractProductT>
		class Factory
		{
			// Interface for concrete products
		public:
			/**
			* Get the name of the type that this factory instantiates.
			* @return The name of the type as a string.
			*/
			virtual std::string ClassName() const = 0;
		private:
			/**
			* Creates a concrete product associated with a concrete product factory.
			* @return The address of the concrete product created on heap.
			*/
			virtual AbstractProductT* Create() = 0;

			// Manager (Singleton)
		public:
			/**
			* Find the concrete product factory associate with a specific class.
			* @param className The name of the class whose associated concrete product factory has to be found.
			* @return The address of the factory which produces instances of class with the name className.
			*/
			static Factory<AbstractProductT>* Find(const std::string& className);
			/**
			* Create an object of the class whose name is passed in.
			* @param className The name of the class whose instance has to be created.
			* @return The address of the concrete product.
			*/
			static AbstractProductT* Create(const std::string& className);
			/**
			* Get an iterator at the beginning of the container of factories.
			* @return The begin iterator of the static hashmap mFactoryTable.
			*/
			static typename Containers::HashMap<std::string, Factory<AbstractProductT>*>::Iterator begin();
			/**
			* Get an iterator beyond the end of the container of factories.
			* @return The end iterator of the static hashmap mFactoryTable.
			*/
			static typename Containers::HashMap<std::string, Factory<AbstractProductT>*>::Iterator end();
		protected:
			/**
			* Add a concrete factory to the list of factories for this abstract factory manager.
			* @param factoryToAdd A reference to the concrete factory which has to be added.
			*/
			static void Add(Factory<AbstractProductT>& factoryToAdd);
			/**
			* Remove a concrete factory to the list of factories for this abstract factory manager.
			* @param factoryToRemove A reference to the concrete factory which has to be removed.
			*/
			static void Remove(Factory<AbstractProductT>& factoryToRemove);
		private:
			/**
			* A static hashmap containing pairs of class names (strings) and pointers to their concrete product factories.
			*/
			static Containers::HashMap<std::string, Factory<AbstractProductT>*> mFactoryTable;
		};
	}
}

#define ConcreteFactory(AbstractProductT, ConcreteProductT)															\
	class ConcreteProductT##Factory : public SiachenGameEngine::GameplayFramework::Factory<AbstractProductT>		\
	{																												\
	public:																											\
		ConcreteProductT##Factory() { Add(*this); }																	\
		~ConcreteProductT##Factory() { Remove(*this); }																\
		virtual std::string ClassName() const override { return (#ConcreteProductT); }								\
		virtual AbstractProductT* Create() override																	\
		{																											\
			AbstractProductT* product = new ConcreteProductT();														\
			assert(product != nullptr);																				\
			return product;																							\
		}																											\
	};

#include "Factory.inl"
