#pragma once
#include "Scope.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class Attributed : public Scope
		{
		RTTI_DECLARATIONS(Attributed, Scope)
		private:
			/**
			* The number of prescribed attributes in this Scope.
			*/
			uint32_t prescribedAttributeCount;
			/**
			* A bool used to ensure that prescribed attributed aren't modified after being assigned.
			*/
			bool prescribedAttributesAssigned;
		public:
			Attributed();

			virtual ~Attributed() = default;
		protected:
			virtual void Populate();

			void AddExternalAttribute(const std::string& attributeName, const std::int32_t* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);
			void AddExternalAttribute(const std::string& attributeName, const std::float_t* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);
			void AddExternalAttribute(const std::string& attributeName, const std::string* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);
			void AddExternalAttribute(const std::string& attributeName, const glm::vec4* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);
			void AddExternalAttribute(const std::string& attributeName, const glm::mat4x4* externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);
			void AddExternalAttribute(const std::string& attributeName, const Scope** externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);
			void AddExternalAttribute(const std::string& attributeName, const RTTI** externalAttribute, std::uint32_t numberOfValues, bool isPrescribedAttribute = false);

			void AddInternalAttribute(const std::string& attributeName, const std::int32_t attributeValue, bool isPrescribedAttribute = false);
			void AddInternalAttribute(const std::string& attributeName, const std::float_t attributeValue, bool isPrescribedAttribute = false);
			void AddInternalAttribute(const std::string& attributeName, const std::string& attributeValue, bool isPrescribedAttribute = false);
			void AddInternalAttribute(const std::string& attributeName, const glm::vec4& attributeValue, bool isPrescribedAttribute = false);
			void AddInternalAttribute(const std::string& attributeName, const glm::mat4x4& attributeValue, bool isPrescribedAttribute = false);
			void AddInternalAttribute(const std::string& attributeName, const Scope* attributeValue, bool isPrescribedAttribute = false);
			void AddInternalAttribute(const std::string& attributeName, const RTTI* attributeValue, bool isPrescribedAttribute = false);

			void SetPrescribedAttributesAssigned();
		};
	}
}