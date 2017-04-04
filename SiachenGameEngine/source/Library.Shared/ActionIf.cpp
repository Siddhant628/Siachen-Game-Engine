#include "pch.h"
#include "ActionIf.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string sThen = "then";
		const std::string sElse = "else";
		const std::string sCondition = "condition";

		RTTI_DEFINITIONS(ActionIf)

		void ActionIf::Populate()
		{
			mThenDatum = &AddInternalAttribute(sThen, DatumType::TableType);
			mElseDatum = &AddInternalAttribute(sElse, DatumType::TableType);
			mConditionDatum = &AddInternalAttribute(sCondition, DatumType::IntegerType);
		}

		ActionIf::ActionIf()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionIf::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			if (mConditionDatum->Get<std::int32_t>())
			{
				assert(mThenDatum == Find(sThen));
				assert(mThenDatum->Get<Scope*>()->Is(Action::TypeIdClass()));
				static_cast<Action*>(mThenDatum->Get<Scope*>())->Update(worldState);
			}
			else
			{
				assert(mElseDatum == Find(sElse));
				assert(mElseDatum->Get<Scope*>()->Is(Action::TypeIdClass()));
				static_cast<Action*>(mElseDatum->Get<Scope*>())->Update(worldState);
			}

			worldState.mAction = GetParent()->As<Action>();
		}
	}
}