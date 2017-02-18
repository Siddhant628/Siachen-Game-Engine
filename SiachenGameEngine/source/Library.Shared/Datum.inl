namespace SiachenGameEngine
{
	namespace Containers
	{
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The item T stored in the datum.
		*/
		template<typename T>
		T& Datum::Get(std::uint32_t index)
		{
			throw std::runtime_error("Invalid type for get operation");
		}

		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The item T stored in the datum.
		*/
		template<typename T>
		const T& Datum::Get(std::uint32_t index) const
		{
			throw std::runtime_error("Invalid type for get operation");
		}

		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The integer stored in the datum.
		*/
		template<>
		std::int32_t& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The floating point number stored in the datum.
		*/
		template<>
		std::float_t& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The vector stored in the datum.
		*/
		template<>
		glm::vec4& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The matrix stored in the datum.
		*/
		template<>
		glm::mat4x4& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The string stored in the datum.
		*/
		template<>
		std::string& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The RTTI* stored in the datum.
		*/
		template<>
		GameplayFramework::RTTI*& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The Scope* stored in the datum.
		*/
		template<>
		GameplayFramework::Scope*& Datum::Get(std::uint32_t index);
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The integer stored in the datum.
		*/
		template<>
		const std::int32_t& Datum::Get(std::uint32_t index) const;
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The floating point number stored in the datum.
		*/
		template<>
		const std::float_t& Datum::Get(std::uint32_t index) const;
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The vector stored in the datum.
		*/
		template<>
		const glm::vec4& Datum::Get(std::uint32_t index) const;
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The matrix stored in the datum.
		*/
		template<>
		const glm::mat4x4& Datum::Get(std::uint32_t index) const;
		/**
		* Get a specific item stored in the datum.
		* @param index The position of the item to retrieve from the datum.
		* @return The string stored in the datum.
		*/
		template<>
		const std::string& Datum::Get(std::uint32_t index) const;
		///**
		//* Get a specific item stored in the datum.
		//* @param index The position of the item to retrieve from the datum.
		//* @return The RTTI* stored in the datum.
		//*/
		//template<>
		//const GameplayFramework::RTTI*& Datum::Get(std::uint32_t index) const;
		///**
		//* Get a specific item stored in the datum.
		//* @param index The position of the item to retrieve from the datum.
		//* @return The Scope* stored in the datum.
		//*/
		//template<>
		//const GameplayFramework::Scope*& Datum::Get(std::uint32_t index) const;

	}
}
