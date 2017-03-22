#include "pch.h"
//
//#include "Attributed.h"
//#include "AttributedBar.h"
//#include "AttributedFoo.h"
//#include "RTTI.h"
//#include "Foo.h"
//
//using namespace SiachenGameEngine::GameplayFramework;
//
//namespace SiachenGameEngine
//{
//	namespace HelperClasses
//	{
//		RTTI_DEFINITIONS(AttributedBar)
//
//		AttributedBar::AttributedBar()
//		{
//			mRTTI = new Foo(100);
//			Populate();
//			UpdatePrescribedAttributeInfo();
//		}
//
//		AttributedBar::AttributedBar(const AttributedBar& rhs) : AttributedFoo(rhs)
//		{
//
//			(*this)["mFloat"].SetStorage(&mFloat, 1U);
//			(*this)["mString"].SetStorage(&mString, 1U);
//			(*this)["mVec4"].SetStorage(&mVec4, 1U);
//			(*this)["mMat4x4"].SetStorage(&mMat4x4, 1U);
//
//			mRTTI = new Foo(rhs.GetRTTIFoo());
//			(*this)["mRTTI"].SetStorage(&mRTTI, 1U);
//
//			(*this)["mFloat"].Set(rhs.GetFloat());
//			(*this)["mString"].Set(rhs.GetString());
//			(*this)["mVec4"].Set(rhs.GetVector());
//			(*this)["mMat4x4"].Set(rhs.GetMatrix());
//
//			SetAuxillaryBegin(rhs.AuxiliaryBegin());
//		}
//
//		AttributedBar& AttributedBar::operator=(const AttributedBar& rhs)
//		{
//			if (this != &rhs)
//			{
//				AttributedFoo::operator=(rhs);
//
//				(*this)["mFloat"].SetStorage(&mFloat, 1U);
//				(*this)["mString"].SetStorage(&mString, 1U);
//				(*this)["mVec4"].SetStorage(&mVec4, 1U);
//				(*this)["mMat4x4"].SetStorage(&mMat4x4, 1U);
//
//				*mRTTI = *rhs.mRTTI;
//				(*this)["mRTTI"].SetStorage(&mRTTI, 1U);
//
//				(*this)["mFloat"].Set(rhs.GetFloat());
//				(*this)["mString"].Set(rhs.GetString());
//				(*this)["mVec4"].Set(rhs.GetVector());
//				(*this)["mMat4x4"].Set(rhs.GetMatrix());
//
//				SetAuxillaryBegin(rhs.AuxiliaryBegin());
//			}
//			return *this;
//		}
//
//		AttributedBar::~AttributedBar()
//		{
//			delete mRTTI;
//		}
//
//		void AttributedBar::Populate()
//		{
//			AddExternalAttribute("mFloat", &mFloat, 1U);
//			AddExternalAttribute("mString", &mString, 1U);
//			AddExternalAttribute("mVec4", &mVec4, 1U);
//			AddExternalAttribute("mMat4x4", &mMat4x4, 1U);
//			AddExternalAttribute("mRTTI", &mRTTI, 1U);
//		}
//
//		std::float_t AttributedBar::GetFloat() const
//		{
//			return mFloat;
//		}
//
//		const std::string AttributedBar::GetString() const
//		{
//			return mString;
//		}
//
//		glm::vec4 AttributedBar::GetVector() const
//		{
//			return mVec4;
//		}
//
//		glm::mat4x4 AttributedBar::GetMatrix() const
//		{
//			return mMat4x4;
//		}
//
//		std::int32_t AttributedBar::GetRTTIFoo() const
//		{
//			Foo* pFoo = mRTTI->As<Foo>();
//			return pFoo->GetValue();
//		}
//
//		void AttributedBar::SetFloat(std::float_t value)
//		{
//			mFloat = value;
//		}
//
//		void AttributedBar::SetString(const std::string& str)
//		{
//			mString = str;
//		}
//
//		void AttributedBar::SetVector(glm::vec4& vec)
//		{
//			mVec4 = vec;
//		}
//
//		void AttributedBar::SetMatrix(glm::mat4x4& matrix)
//		{
//			mMat4x4 = matrix;
//		}
//
//		void AttributedBar::SetRTTIFoo(std::int32_t value)
//		{
//			Foo* pFoo = mRTTI->As<Foo>();
//			pFoo->SetValue(value);
//		}
//	}
//}
