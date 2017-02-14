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

			Datum stringDatum;
			std::string str = "str";
			Assert::AreEqual(stringDatum.Size(), 0U);
			stringDatum.PushBack(str);
			Assert::AreEqual(stringDatum.Size(), 1U);

			Datum vectorDatum;
			glm::vec4 vec(1.0f);
			Assert::AreEqual(vectorDatum.Size(), 0U);
			vectorDatum.PushBack(vec);
			Assert::AreEqual(vectorDatum.Size(), 1U);

			Datum matDatum;
			glm::mat4x4 mat;
			Assert::AreEqual(matDatum.Size(), 0U);
			matDatum.PushBack(mat);
			Assert::AreEqual(matDatum.Size(), 1U);
		}

		TEST_METHOD(Datum_IsEmpty)
		{
			Datum intDatum;
			Assert::IsTrue(intDatum.IsEmpty());
			intDatum.PushBack(10);
			Assert::IsFalse(intDatum.IsEmpty());

			Datum floatDatum;
			Assert::IsTrue(floatDatum.IsEmpty());
			floatDatum.PushBack(10.0f);
			Assert::IsFalse(floatDatum.IsEmpty());

			Datum stringDatum;
			Assert::IsTrue(stringDatum.IsEmpty());
			stringDatum.PushBack(std::string("str"));
			Assert::IsFalse(stringDatum.IsEmpty());

			Datum vectorDatum;
			Assert::IsTrue(vectorDatum.IsEmpty());
			vectorDatum.PushBack(glm::vec4(1.0f));
			Assert::IsFalse(vectorDatum.IsEmpty());

			Datum matDatum;
			Assert::IsTrue(matDatum.IsEmpty());
			matDatum.PushBack(glm::mat4x4());
			Assert::IsFalse(matDatum.IsEmpty());
		}

		TEST_METHOD(Datum_Reserve)
		{
			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);
			
			auto intExpression = [&intDatum] { intDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(intExpression);
			intDatum.Reserve(5);
			Assert::AreEqual(intData, intDatum.Get<std::int32_t>());
			
			intDatum.SetStorage(&intData, 1);
			auto intExpression2 = [&intDatum] { intDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(intExpression2);

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);

			auto floatExpression = [&floatDatum] { floatDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(floatExpression);
			floatDatum.Reserve(5);
			Assert::AreEqual(floatData, floatDatum.Get<std::float_t>());

			floatDatum.SetStorage(&floatData, 1);
			auto floatExpression2 = [&floatDatum] { floatDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(floatExpression2);

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);

			auto stringExpression = [&stringDatum] { stringDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(stringExpression);
			stringDatum.Reserve(5);
			Assert::AreEqual(stringData, stringDatum.Get<std::string>());

			stringDatum.SetStorage(&stringData, 1);
			auto stringExpression2 = [&stringDatum] { stringDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(stringExpression2);

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);

			auto vecExpression = [&vectorDatum] { vectorDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(vecExpression);
			vectorDatum.Reserve(5);
			Assert::IsTrue(vecData == vectorDatum.Get<glm::vec4>());

			vectorDatum.SetStorage(&vecData, 1);
			auto vecExpression2 = [&vectorDatum] { vectorDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(vecExpression2);

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);

			auto matExpression = [&matDatum] { matDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(matExpression);
			matDatum.Reserve(5);
			Assert::IsTrue(matData == matDatum.Get<glm::mat4x4>());

			matDatum.SetStorage(&matData, 1);
			auto matExpression2 = [&matDatum] { matDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(matExpression2);
		}

		TEST_METHOD(Datum_PushBack)
		{
			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			
			intDatum.PushBack(intData);
			Assert::IsTrue(intData == intDatum.Get<std::int32_t>());



			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			
			floatDatum.PushBack(floatData);
			Assert::IsTrue(intData == intDatum.Get<std::int32_t>());

			

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}