#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
	public:
		
		TEST_METHOD(SListConstructors)
		{
			int data = 1;
			SList list(data);
			Assert::AreEqual(data, list.GetData());
		}

	};
}