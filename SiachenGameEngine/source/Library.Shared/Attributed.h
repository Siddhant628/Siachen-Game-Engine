#pragma once

#include "Scope.h"
#include "RTTI.h"
#include "Vector.h"
#include "HashMap.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/**
		* Attributed class provides utilities to Scope to glue the Scope with native objects in C++. It provides a mechanism to access data from the scripts.
		*/
		class Attributed : public Scope
		{
		RTTI_DECLARATIONS(Attributed, Scope)

		private:
			typedef Containers::HashMap<std::uint64_t, Containers::Vector<std::string>> CacheHashmapType;

			/**
			* A hashmap containing <class ID, vector of strings> pairs. The vectors are used to store names of prescribed attributes for different classes.
			*/
			static CacheHashmapType sPrescribedAttributeCache;
			/**
			* The number of prescribed attributes in this Scope.
			*/
			std::uint32_t mPrescribedAttributeCount;

		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate();

			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const std::int32_t* externalAttribute, std::uint32_t numberOfValues);
			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const std::float_t* externalAttribute, std::uint32_t numberOfValues);
			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const std::string* externalAttribute, std::uint32_t numberOfValues);
			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const glm::vec4* externalAttribute, std::uint32_t numberOfValues);
			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const glm::mat4x4* externalAttribute, std::uint32_t numberOfValues);
			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const Scope** externalAttribute, std::uint32_t numberOfValues);
			/**
			* Add an external attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param externalAttribute A pointer to the value of the external attribute which has to be added to this scope.
			* @param numberOfValues The number of items in the external attribute.
			*/
			void AddExternalAttribute(const std::string& attributeName, const RTTI** externalAttribute, std::uint32_t numberOfValues);

			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const std::int32_t attributeValue);
			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const std::float_t attributeValue);
			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const std::string& attributeValue);
			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const glm::vec4& attributeValue);
			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const glm::mat4x4& attributeValue);
			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const Scope* attributeValue);
			/**
			* Add an internal attribute to the scope associated with this attributed class object.
			* @param attributeName The name of the attribute which has to be appended to the scope.
			* @param attributeValue The value of the attribute which has to be added to the scope.
			*/
			void AddInternalAttribute(const std::string& attributeName, const RTTI* attributeValue);

			/**
			* Updates the cache hashmap with the attributes present in the scope at the instance it is called. This method should be called as soon as the scope is populated with prescribed attributes.
			*/
			void UpdatePrescribedAttributeCache();

		public:
			/**
			* Default Constructor - Creates an empty scope and populates it with the prescribed attributes.
			*/
			Attributed();
			/**
			* Destructor clears and frees all the memory reserved by the vector.
			*/
			virtual ~Attributed() = default;

			/**
			* Check whether a string is an attribute.
			* @param attributeName The string to check for if it is an attribute.
			* @param True if attributeName is an attribute.
			*/
			bool IsAttribute(const std::string& attributeName) const;
			/**
			* Check whether a string is a prescribed attribute.
			* @param attributeName The string to check for if it is a prescribed attribute.
			* @param True if attributeName is a prescribed attribute.
			*/
			bool IsPrescribedAttribute(const std::string& attributeName) const;
			/**
			* Check whether a string is a auxiliary attribute.
			* @param attributeName The string to check for if it is a auxiliary attribute.
			* @param True if attributeName is a auxiliary attribute.
			*/
			bool IsAuxiliaryAttribute(const std::string& attributeName) const;

			/**
			* Append a datum to the scope with this attribute name or return a reference to one already present.
			* @param attributeName Name of the attribute which is has to appended to this scope.
			* @return A reference to the datum in the scope which is associated with this attribute.
			*/
			Containers::Datum& AppendAuxiliaryAttribute(const std::string& attributeName);
			/**
			* Get the index of the first auxiliary attribute in the scope.
			* @return The index of the first auxiliary attribute.
			*/
			std::uint32_t AuxiliaryBegin() const;
		};
	}
}