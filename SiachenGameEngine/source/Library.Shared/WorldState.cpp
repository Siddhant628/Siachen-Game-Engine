#include "pch.h"
#include "WorldState.h"

using namespace SiachenGameEngine::Library;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		WorldState::WorldState() : mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr)
		{

		}

		void WorldState::SetGameTime(const Library::GameTime& gameTime)
		{
			mGameTime = gameTime;
		}

		const GameTime& WorldState::GetGameTime() const
		{
			return mGameTime;
		}


	}
}