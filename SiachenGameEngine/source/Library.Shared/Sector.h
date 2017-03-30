#pragma once
#include "Attributed.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class Sector final : public Attributed
		{
			RTTI_DECLARATIONS(Sector, Attributed)
		public:
			Sector();

			~Sector() = default;

			virtual void Populate() override;

			const std::string& Name() const;

			void SetName(const std::string& sectorName);


		private:
			std::string mSectorName;
		};
	}
}