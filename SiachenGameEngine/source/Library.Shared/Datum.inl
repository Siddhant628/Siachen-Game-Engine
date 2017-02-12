namespace SiachenGameEngine
{
	namespace Containers
	{
		template <>
		std::int32_t& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::IntegerType)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index into the datum.");
			}
			return mData.i[index];
		}

		template<>
		std::float_t& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::FloatType)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index into the datum.");
			}
			return mData.f[index];
		}

		template<>
		glm::vec4& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::VectorType)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index into the datum.");
			}
			return mData.v[index];
		}

		template<>
		glm::mat4x4& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::MatrixType)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index into the datum.");
			}
			return mData.m[index];
		}

		template<>
		std::string& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::StringType)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index into the datum.");
			}
			return mData.s[index];
		}

		template<>
		GameplayFramework::RTTI*& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::PointerType)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index into the datum.");
			}
			return mData.r[index];
		}
	}
}