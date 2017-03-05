#pragma once

#include "RTTI.h"

#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/*
		* A scope is a table that creates a dictionary of name-value pairs where Datum objects are the values. 
		*/
		class Scope : public RTTI
		{
			RTTI_DECLARATIONS(Scope, RTTI)
			
		private:

			typedef std::pair<std::string, Containers::Datum> StringDatumPair;
			typedef Containers::HashMap<std::string, Containers::Datum> TableType;
			typedef Containers::Vector<StringDatumPair*> VectorType;
			/*
			* The hash map which forms up the table. It stores string-datum pairs.
			*/
			TableType mTableHashmap;
			/*
			* The index vector which stores pointers to string-datum pairs inside the table, in their order of insertion.
			*/
			VectorType mIndexVector;
			/*
			* The pointer to a scope which is a parent to this scope.
			*/
			Scope* mParent;
			/*
			* Preforms a deep copy of a scope into this one.
			* @param rhs The scope whose deep copy is to be performed.
			*/
			void DeepCopyScope(const Scope& rhs);

		public:
			/*
			* Default Constructor - Creates a default constructed scope with the specified capacity of its hash map.
			* @param initialCapacity The initial capacity of the scope's hash map.
			*/
			explicit Scope(std::uint32_t initialCapacity = 13);
			/*
			* Copy constructor - Performs a deep copy of rhs into this scope.
			* @param rhs The scope which has to be copied into this.
			*/
			Scope(const Scope& rhs);
			/*
			* Assignment Operator - Performs a deep copy of rhs into this scope.
			* @param rhs The scope which has to be deep copied into this scope.
			* @return A reference to a scope with a deep copy of rhs.
			*/
			Scope& operator=(const Scope& rhs);
			/*
			* Destructor - Clears the dynamically allocated memory.
			*/
			virtual ~Scope();
			/*
			* Returns a reference to a datum present in the scope with the parameter as key. If it is not present, creates one and returns a reference to it.
			* @param key The key which is associated with a name-datum pair in the scope.
			* @return A reference to the found / appended datum from the key-datum pair.
			*/
			Containers::Datum& Append(const std::string& key);
			/*
			* Appends a scope to this one and returns a reference to it.
			* @param key The name for the name-datum pair inside this scope where this scope should be appended. If key isn't present, creates a datum with the key in its pair.
			* @return A reference to the appended scope.
			*/
			Scope& AppendScope(const std::string& key);
			/*
			* Finds a pair in the scope with the associated key.
			* @param key The key which has to be found in the scope.
			* @return A pointer to a Datum which is present in the name-datum pair for the parameter key.
			*/
			Containers::Datum* Find(const std::string& key) const;
			/*
			* Searches for a datum with the associated key in this scope and its parents recursively.
			* @param key The key which has to be found in the scope or its parents.
			* @param owningScope An output parameter which has a pointer to the scope in which the key was found.
			* @return A pointer to a Datum which is present in the name-datum pair for the parameter key.
			*/
			Containers::Datum* Search(const std::string& key, Scope** owningScope = nullptr) const;
			/*
			* Get a pointer to the parent of this scope.
			* @return A pointer to the scope which is the parent of this scope.
			*/
			Scope* GetParent() const;
			/*
			* Compares the parameter scope with this scope.
			* @param rhs A pointer to a scope which has to be compared with this.
			* @return True if the two scopes are equal.
			*/
			virtual bool Equals(const RTTI* rhs) const override;
			/*
			* Get a string version of this scope.
			* @return A string version of this scope.
			*/
			virtual std::string ToString() const override;
			/*
			* A wrapper for the Append method.
			* @param key The key which is associated with a name-datum pair in the scope.
			* @return A reference to the found / appended datum from the key-datum pair.
			*/
			Containers::Datum& operator[](const std::string& key);
			/*
			* Get a reference to the datum which was inserted at a specific index in the order vector.
			* @param index The index in the order vector from which the datum has to be retrieved.
			* @return A reference to the datum in the scope which was inserted in the specific order.
			*/
			Containers::Datum& operator[](const std::uint32_t index);
			/*
			* Get a reference to the datum which was inserted at a specific index in the order vector.
			* @param index The index in the order vector from which the datum has to be retrieved.
			* @return A reference to the datum in the scope which was inserted in the specific order.
			*/
			const Containers::Datum& operator[](const std::uint32_t index) const;
			/*
			* Decouples this scope from its parent and removes its pointer from the parent's table type datum.
			* @return True if a scope turned into an orphan scope.
			*/
			bool Orphan();
			/*
			* Adds the parameter scope to this scope's children.
			* @param childToAdopt The scope which has to be adopted.
			* @param nameOfChild The name in the name-datum pair where the child should be appended.
			*/
			void Adopt(Scope& childToAdopt, const std::string& nameOfChild);
			/*
			* Clears all the dynamically allocated memory by the scope by destroying all of its children. Also, clears the order vector and the scope hash map.
			*/
			void Clear();
			/*
			* Compares two scopes for equality.
			* @param rhs The scope with which this scope should be compared.
			* @return True if the two scopes are equal.
			*/
			bool operator==(const Scope& rhs) const;
			/*
			* Compares two scopes for inequality.
			* @param rhs The scope with which this scope should be compared.
			* @return True if the two scopes are not equal.
			*/
			bool operator!=(const Scope& rhs) const;
			/**
			* Get the keys present inside the current scope (excluding children scope).
			* @param keysVector An output parameter which will be a vector of strings (keys).
			*/
			void GetKeys(Containers::Vector<std::string>& keysVector);
		};
	}
}