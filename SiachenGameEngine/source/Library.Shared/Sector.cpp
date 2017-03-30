#include "pch.h"
#include "Sector.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Sector)

		Sector::Sector()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void Sector::Populate()
		{
			AddExternalAttribute("name", &mSectorName, 1U);
		}

		const std::string& Sector::Name() const
		{
			return mSectorName;
		}

		void Sector::SetName(const std::string& sectorName)
		{
			mSectorName = sectorName;
		}


	}
}