#pragma once
#include "HashMap.h"

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
			* Creates a concrete product associated with a concrete factory.
			* @return The address of the concrete product.
			*/
			virtual AbstractProductT* Create() = 0;

			// Manager (Singleton)
		public:
			/**
			* Find the concrete factory associate with a specific class.
			* @param className The name of the class whose associated concrete factory has to be found.
			* @return The address of the factory which produces instances of class with the name className.
			*/
			static Factory<AbstractProductT>* Find(const std::string& className);
			/**
			* Create an object of the class whose name is passed in.
			* @param className The name of the class whose instance has to be created.
			* @return The address of the concrete product.
			*/
			static AbstractProductT* Create(const std::string& className);
		protected:
			/**
			* Add a concrete factory to the list of factories for this abstract factory.
			* @param factoryToAdd A reference to the concrete factory which has to be added.
			*/
			static void Add(Factory<AbstractProductT>& factoryToAdd);
			/**
			* Remove a concrete factory to the list of factories for this abstract factory.
			* @param factoryToRemove A reference to the concrete factory which has to be removed.
			*/
			static void Remove(Factory<AbstractProductT>& factoryToRemove);
		private:
			static Containers::HashMap<std::string, Factory<AbstractProductT>*> mFactoryTable;

			// TODO Write begin()
			// TODO Write end()
		};
	}


#define ConcreteFactory(AbstractProductT, ConcreteProductT)								\
	class ConcreteProductT##Factory : public Factory<AbstractProductT>					\
	{																					\
	public:																				\
		ConcreteProductT##Factory() { Add(*this); }										\
		~ConcreteProductT##Factory() { Remove(*this); }									\
		virtual std::string ClassName() const override { return (#ConcreteProductT); }	\
		virtual AbstractProductT* Create() override										\
		{																				\
			AbstractProductT* product = new ConcreteProductT();							\
			/*assert(product != nullptr);*/												\
			return product;																\
		}																				\
	};
}

#include "Factory.inl"
