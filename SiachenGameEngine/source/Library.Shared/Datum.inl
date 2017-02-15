namespace SiachenGameEngine
{
	namespace Containers
	{
		template <>
		std::int32_t& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::IntegerType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.i[index];
		}

		template<>
		std::float_t& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::FloatType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.f[index];
		}

		template<>
		glm::vec4& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::VectorType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.v[index];
		}

		template<>
		glm::mat4x4& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::MatrixType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.m[index];
		}

		template<>
		std::string& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::StringType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.s[index];
		}

		template<>
		GameplayFramework::RTTI*& Datum::Get(std::uint32_t index) const
		{
			if (mDatumType != DatumType::PointerType || index >= mSize)
			{
				throw std::runtime_error("Invalid get operation.");
			}
			return mData.r[index];
		}
	}
}