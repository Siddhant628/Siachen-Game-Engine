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
			Datum floatDatum;
			floatDatum.SetType(DatumType::FloatType);
			floatDatum.PushBack(2.0f);
			Assert::AreEqual(2.0f, floatDatum.Get<float_t>());

			Datum intDatum;
			intDatum.SetType(DatumType::IntegerType);
			intDatum.PushBack(5);
			intDatum.PushBack(8);
			intDatum.PushBack(11);
			intDatum.PopBack();
			Assert::AreEqual(8, intDatum.Get<int>(1U));
		}

		// TODO 
		TEST_METHOD(Datum_Constructors)
		{

		}
		// TODO
		TEST_METHOD(Datum_Assignment_Operator)
		{

		}

		TEST_METHOD(Datum_Type)
		{
			Datum intDatum;
			intDatum.SetType(DatumType::IntegerType);
			Assert::IsTrue(DatumType::IntegerType == intDatum.Type());

			Datum floatDatum;
			floatDatum.SetType(DatumType::FloatType);
			Assert::IsTrue(DatumType::FloatType == floatDatum.Type());

			Datum stringDatum;
			stringDatum.SetType(DatumType::StringType);
			Assert::IsTrue(DatumType::StringType == stringDatum.Type());

			Datum vectorDatum;
			vectorDatum.SetType(DatumType::VectorType);
			Assert::IsTrue(DatumType::VectorType == vectorDatum.Type());

			Datum matDatum;
			matDatum.SetType(DatumType::VectorType);
			Assert::IsTrue(DatumType::VectorType == matDatum.Type());

			Datum ptrDatum;
			ptrDatum.SetType(DatumType::PointerType);
			Assert::IsTrue(DatumType::PointerType == ptrDatum.Type());
		}

		TEST_METHOD(Datum_SetType)
		{
			Datum intDatum;
			intDatum.SetType(DatumType::IntegerType);
			auto intExpression = [&intDatum] {intDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(intExpression);

			Datum floatDatum;
			floatDatum.SetType(DatumType::FloatType);
			auto floatExpression = [&floatDatum] {floatDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(floatExpression);

			Datum stringDatum;
			stringDatum.SetType(DatumType::StringType);
			auto stringExpression = [&stringDatum] {stringDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(stringExpression);

			Datum vectorDatum;
			vectorDatum.SetType(DatumType::VectorType);
			auto vectorExpression = [&vectorDatum] {vectorDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(vectorExpression);

			Datum matDatum;
			matDatum.SetType(DatumType::MatrixType);
			auto matExpression = [&matDatum] {matDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(matExpression);
			
			Datum ptrDatum;
			ptrDatum.SetType(DatumType::PointerType);
			auto ptrExpression = [&ptrDatum] {ptrDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(ptrExpression);
		}

		TEST_METHOD(DatumType_Size)
		{
			Datum intDatum;
			Assert::AreEqual(intDatum.Size(), 0U);
			intDatum.PushBack(10);
			Assert::AreEqual(intDatum.Size(), 1U);

			Datum floatDatum;
			Assert::AreEqual(floatDatum.Size(), 0U);
			floatDatum.PushBack(10.0f);
			Assert::AreEqual(floatDatum.Size(), 1U);

			//Datum stringDatum;
			//std::string str = "str";
			//Assert::AreEqual(stringDatum.Size(), 0U);
			//stringDatum.PushBack(str);
			//Assert::AreEqual(stringDatum.Size(), 1U);

			//Datum vectorDatum;
			//glm::vec4 vec(1.0f);
			//Assert::AreEqual(vectorDatum.Size(), 0U);
			//vectorDatum.PushBack(vec);
			//Assert::AreEqual(vectorDatum.Size(), 1U);

			//Datum matDatum;
			//Assert::AreEqual(intDatum.Size(), 0U);
			//intDatum.PushBack(10);
			//Assert::AreEqual(intDatum.Size(), 1U);

			//Datum ptrDatum;
			//Assert::AreEqual(intDatum.Size(), 0U);
			//intDatum.PushBack(10);
			//Assert::AreEqual(intDatum.Size(), 1U);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}