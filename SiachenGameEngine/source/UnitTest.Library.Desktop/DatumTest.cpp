#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Containers;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(Datum_First)
		{
			//Datum floatDatum;
			//floatDatum.SetType(DatumType::FloatType);
			//floatDatum.PushBack(2.0f);

			Datum intDatum;
			intDatum.SetType(DatumType::IntegerType);
			intDatum.PushBack(5);
			intDatum.PushBack(8);
			intDatum.PushBack(11);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}