#include "pch.h"

#include "AttributedBaz.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(AttributedBaz)

		void AttributedBaz::DeepCopyAttributedBaz(const AttributedBaz& rhs)
		{
			Attributed::operator=(rhs);

			SetAuxillaryBegin(rhs.AuxiliaryBegin());
		}

		AttributedBaz::AttributedBaz()
		{
			foo = new Foo(123);
			foo2 = new Foo(321);
			scope = new Scope();
			(*scope)["Butter"] = "Chicken";

			Populate();
			UpdatePrescribedAttributeInfo();
		}

		AttributedBaz::AttributedBaz(const AttributedBaz& rhs)
		{
			DeepCopyAttributedBaz(rhs);
		}

		AttributedBaz & AttributedBaz::operator=(const AttributedBaz& rhs)
		{
			if (this != &rhs)
			{
				Clear();
				DeepCopyAttributedBaz(rhs);
			}
			return *this;
		}

		AttributedBaz::~AttributedBaz()
		{
			delete foo;
			delete foo2;
			delete scope;
		}

		void AttributedBaz::Populate()
		{
			glm::vec4 vec(10.0f, 11.0f, 12.0f, 13.0f);
			glm::mat4x4 mat(vec, vec, vec, vec);

			AddExternalAttribute("mInteger", &mInteger, 1U);

			AddInternalAttribute("iInt", 0);
			AddInternalAttribute("iFloat", 10.0f);
			AddInternalAttribute("iString", "Butter");
			AddInternalAttribute("iVector", glm::vec4());
			AddInternalAttribute("iMatrix", glm::mat4x4());
			AddInternalAttribute("iRTTI", foo);
			

			AddInternalAttribute("iInt", 10);
			AddInternalAttribute("iFloat", 20.0f);
			AddInternalAttribute("iString", "Chicken");
			AddInternalAttribute("iVector", vec);
			AddInternalAttribute("iMatrix", mat);
			AddInternalAttribute("iRTTI", foo2);
			AddInternalAttribute("iScope", scope);

		}
	}
}
