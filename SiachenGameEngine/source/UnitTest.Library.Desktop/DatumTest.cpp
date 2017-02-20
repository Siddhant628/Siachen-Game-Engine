#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "Scope.h"

#define GLM_FORCE_CXX98
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;

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
		
		
		TEST_METHOD(Datum_Copy_Constructor)
		{
			// Tests for integers
			std::int32_t intData = 10;

			Datum intDatum;
			intDatum.PushBack(intData);
			Datum intDatum2(intDatum);
			Assert::IsTrue(intDatum == intDatum2);

			intDatum.SetStorage(&intData, 1);
			Datum intDatum3(intDatum);
			Assert::IsTrue(intDatum == intDatum3);

			// Tests for floats
			std::float_t floatData = 10.0f;

			Datum floatDatum;
			floatDatum.PushBack(floatData);
			Datum floatDatum2(floatDatum);
			Assert::IsTrue(floatDatum == floatDatum2);

			floatDatum.SetStorage(&floatData, 1);
			Datum floatDatum3(floatDatum);
			Assert::IsTrue(floatDatum == floatDatum3);

			// Tests for strings
			std::string stringData = "str", stringData2 = "str2";

			Datum stringDatum;
			stringDatum.PushBack(stringData);
			Datum stringDatum2(stringDatum);
			Assert::IsTrue(stringDatum == stringDatum2);

			stringDatum.SetStorage(&stringData, 1);
			Datum stringDatum3(stringDatum);
			Assert::IsTrue(stringDatum == stringDatum3);

			// Tests for vectors
			glm::vec4 vecData(1.0f);

			Datum vectorDatum;
			vectorDatum.PushBack(vecData);
			Datum vectorDatum2(vectorDatum);
			Assert::IsTrue(vectorDatum == vectorDatum2);

			vectorDatum.SetStorage(&vecData, 1);
			Datum vectorDatum3(vectorDatum);
			Assert::IsTrue(vectorDatum == vectorDatum3);

			// Tests for matrices
			glm::mat4x4 matData;

			Datum matDatum;
			matDatum.PushBack(matData);
			Datum matDatum2(matDatum);
			Assert::IsTrue(matDatum == matDatum2);

			matDatum.SetStorage(&matData, 1);
			Datum matDatum3(matDatum);
			Assert::IsTrue(matDatum == matDatum3);

			// Test for tables

			Scope scope;
			scope.Append(stringData).PushBack(intData);
			Scope* scope1 = &scope;

			Datum scopeDatum;
			scopeDatum.PushBack(&scope);
			Datum scopeDatum2(scopeDatum);

			Assert::IsTrue(scopeDatum == scopeDatum2);

			scopeDatum.SetStorage(&scope1, 1);
			Datum scopeDatum3(scopeDatum);
			Assert::IsTrue(scopeDatum3 == scopeDatum);
		}
		
		TEST_METHOD(Datum_Assignment_Operator)
		{
			// Tests for integers
			std::int32_t intData = 10;

			Datum intDatum;
			intDatum.PushBack(intData);
			Datum intDatum2;
			intDatum2 = intDatum;
			Assert::IsTrue(intDatum == intDatum2);

			intDatum.SetStorage(&intData, 1);
			Datum intDatum3 = intDatum;
			Assert::IsTrue(intDatum == intDatum3);

			// Tests for floats
			std::float_t floatData = 10.0f;

			Datum floatDatum;
			floatDatum.PushBack(floatData);
			Datum floatDatum2;
			floatDatum2 = floatDatum;
			Assert::IsTrue(floatDatum == floatDatum2);

			floatDatum.SetStorage(&floatData, 1);
			Datum floatDatum3;
			floatDatum3 = floatDatum;
			Assert::IsTrue(floatDatum == floatDatum3);

			// Tests for strings
			std::string stringData = "str";

			Datum stringDatum;
			stringDatum.PushBack(stringData);
			Datum stringDatum2;
			stringDatum2 = stringDatum;
			Assert::IsTrue(stringDatum == stringDatum2);

			stringDatum.SetStorage(&stringData, 1);
			Datum stringDatum3;
			stringDatum3 = stringDatum;
			Assert::IsTrue(stringDatum == stringDatum3);

			// Tests for vectors
			glm::vec4 vecData(1.0f);

			Datum vectorDatum;
			vectorDatum.PushBack(vecData);
			Datum vectorDatum2;
			vectorDatum2 = vectorDatum;
			Assert::IsTrue(vectorDatum == vectorDatum2);

			vectorDatum.SetStorage(&vecData, 1);
			Datum vectorDatum3;
			vectorDatum3 = vectorDatum;
			Assert::IsTrue(vectorDatum == vectorDatum3);

			// Tests for matrices
			glm::mat4x4 matData;

			Datum matDatum;
			matDatum.PushBack(matData);
			Datum matDatum2;
			matDatum2 = matDatum;
			Assert::IsTrue(matDatum == matDatum2);

			matDatum.SetStorage(&matData, 1);
			Datum matDatum3;
			matDatum3 = matDatum;
			Assert::IsTrue(matDatum == matDatum3);

			// Test for tables

			Scope scope, scope2;
			Scope* scope1 = &scope;
			scope.Append(stringData).PushBack(intData);

			Datum scopeDatum;
			scopeDatum.PushBack(&scope);
			Datum scopeDatum2;
			scopeDatum2 = scopeDatum;
			Assert::IsTrue(scopeDatum == scopeDatum2);

			scopeDatum.SetStorage(&scope1, 1);
			Datum scopeDatum3 = scopeDatum;
			Assert::IsTrue(scopeDatum == scopeDatum3);
		}
		
		TEST_METHOD(Datum_Assignment_Scalar_Operator)
		{
			Datum pointerDatum;
			pointerDatum.SetType(DatumType::PointerType);

			// Tests for integers
			std::int32_t intData = 10, intData2 = 20;

			Datum intDatum;
			intDatum = intData;
			Assert::IsTrue(intData == intDatum.Get<std::int32_t>());
			intDatum = intData2;
			Assert::IsTrue(intData2 == intDatum.Get<std::int32_t>());

			auto intExpression = [&pointerDatum, &intData] { pointerDatum = intData; };
			Assert::ExpectException<std::exception>(intExpression);

			// Tests for floats
			std::float_t floatData = 10.0f, floatData2 = 20.0f;

			Datum floatDatum;
			floatDatum = floatData;
			Assert::IsTrue(floatData == floatDatum.Get<std::float_t>());
			floatDatum = floatData2;
			Assert::IsTrue(floatData2 == floatDatum.Get<std::float_t>());

			auto floatExpression = [&pointerDatum, &floatData] { pointerDatum = floatData; };
			Assert::ExpectException<std::exception>(floatExpression);

			// Tests for strings
			std::string stringData = "str", stringData2 = "str2";

			Datum stringDatum;
			stringDatum = stringData;
			Assert::IsTrue(stringData == stringDatum.Get<std::string>());
			stringDatum = stringData2;
			Assert::IsTrue(stringData2 == stringDatum.Get<std::string>());

			auto strExpression = [&pointerDatum, &stringData] { pointerDatum = stringData; };
			Assert::ExpectException<std::exception>(strExpression);

			// Tests for vectors
			glm::vec4 vecData(1.0f), vecData2(2.0f);

			Datum vectorDatum;
			vectorDatum = vecData;
			Assert::IsTrue(vecData == vectorDatum.Get<glm::vec4>());
			vectorDatum = vecData2;
			Assert::IsTrue(vecData2 == vectorDatum.Get<glm::vec4>());

			auto vecExpression = [&pointerDatum, &vecData] { pointerDatum = vecData; };
			Assert::ExpectException<std::exception>(vecExpression);

			// Tests for matrices
			glm::mat4x4 matData(vecData2, vecData2, vecData, vecData), matData2(vecData, vecData, vecData2, vecData2);

			Datum matDatum;
			matDatum = matData;
			Assert::IsTrue(matData == matDatum.Get<glm::mat4x4>());
			matDatum = matData2;
			Assert::IsTrue(matData2 == matDatum.Get<glm::mat4x4>());

			auto matExpression = [&pointerDatum, &matData] { pointerDatum = matData; };
			Assert::ExpectException<std::exception>(matExpression);

			// Tests for tables
			Scope scope, scope2;
			scope["IntegerData"] = 10 ;

			Datum scopeDatum;
			scopeDatum = &scope;
			Assert::IsTrue(&scope == scopeDatum.Get<Scope*>());
			scopeDatum = &scope2;
			Assert::IsTrue(&scope2 == scopeDatum.Get<Scope*>());

			auto scopeExpression = [&pointerDatum, &scope] { pointerDatum = &scope; };
			Assert::ExpectException<std::exception>(scopeExpression);
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

			Datum scopeDatum;
			scopeDatum.SetType(DatumType::TableType);
			Assert::IsTrue(DatumType::TableType == scopeDatum.Type());
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

			Datum scopeDatum;
			scopeDatum.SetType(DatumType::TableType);
			auto scopeExpression = [&scopeDatum] {scopeDatum.SetType(DatumType::UnknownType); };
			Assert::ExpectException<std::exception>(scopeExpression);
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

			Datum scopeDatum;
			Scope scope;
			Assert::AreEqual(scopeDatum.Size(), 0U);
			scopeDatum.PushBack(&scope);
			Assert::AreEqual(scopeDatum.Size(), 1U);
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

			Datum scopeDatum;
			Scope scope;
			Assert::IsTrue(scopeDatum.IsEmpty());
			scopeDatum.PushBack(&scope);
			Assert::IsFalse(scopeDatum.IsEmpty());
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

			// Tests for integers
			Scope scope;
			Scope* scopePtr = &scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);

			auto scopeExpression = [&scopeDatum] { scopeDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(scopeExpression);
			scopeDatum.Reserve(5);
			Assert::IsTrue(&scope == scopeDatum.Get<Scope*>());

			scopeDatum.SetStorage(&scopePtr, 1);
			auto scopeExpression2 = [&scopeDatum] { scopeDatum.Reserve(0); };
			Assert::ExpectException<std::exception>(scopeExpression2);
		}
		
		TEST_METHOD(Datum_PushBack)
		{
			Datum pointerDatum;
			pointerDatum.SetType(DatumType::PointerType);

			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;

			intDatum.PushBack(intData);
			Assert::IsTrue(intData == intDatum.Get<std::int32_t>());

			auto intExpression = [&pointerDatum, &intData] { pointerDatum.PushBack(intData); };
			Assert::ExpectException<std::exception>(intExpression);

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			
			floatDatum.PushBack(floatData);
			Assert::IsTrue(intData == floatDatum.Get<float_t>());

			auto floatExpression = [&pointerDatum, &floatData] { pointerDatum.PushBack(floatData); };
			Assert::ExpectException<std::exception>(floatExpression);

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);

			stringDatum.PushBack(stringData);
			Assert::IsTrue(stringData == stringDatum.Get<std::string>());

			auto strExpression = [&pointerDatum, &stringData] { pointerDatum.PushBack(stringData); };
			Assert::ExpectException<std::exception>(strExpression);

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);

			vectorDatum.PushBack(vecData);
			Assert::IsTrue(vecData == vectorDatum.Get<glm::vec4>());

			auto vecExpression = [&pointerDatum, &vecData] { pointerDatum.PushBack(vecData); };
			Assert::ExpectException<std::exception>(vecExpression);

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);

			matDatum.PushBack(matData);
			Assert::IsTrue(matData == matDatum.Get<glm::mat4x4>());

			auto matExpression = [&pointerDatum, &matData] { pointerDatum.PushBack(matData); };
			Assert::ExpectException<std::exception>(matExpression);

			// Test for tables

			Scope scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);

			scopeDatum.PushBack(&scope);
			Assert::IsTrue(&scope == scopeDatum.Get<Scope*>());

			auto scopeExpression = [&pointerDatum, &scope] { pointerDatum.PushBack(&scope); };
			Assert::ExpectException<std::exception>(scopeExpression);

		}
		
		TEST_METHOD(Datum_PopBack)
		{
			Datum unknownDatum;
			
			auto unknownExpression = [&unknownDatum] {unknownDatum.PopBack(); };
			Assert::ExpectException<std::exception>(unknownExpression);

			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);
			Assert::AreEqual(intDatum.Size(), 1U);
			intDatum.PopBack();
			Assert::AreEqual(intDatum.Size(), 0U);
			intDatum.PopBack();

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);
			Assert::AreEqual(floatDatum.Size(), 1U);
			floatDatum.PopBack();
			Assert::AreEqual(floatDatum.Size(), 0U);
			floatDatum.PopBack();

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);
			Assert::AreEqual(stringDatum.Size(), 1U);
			stringDatum.PopBack();
			Assert::AreEqual(stringDatum.Size(), 0U);
			stringDatum.PopBack();

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);
			Assert::AreEqual(vectorDatum.Size(), 1U);
			vectorDatum.PopBack();
			Assert::AreEqual(vectorDatum.Size(), 0U);
			vectorDatum.PopBack();

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);
			Assert::AreEqual(matDatum.Size(), 1U);
			matDatum.PopBack();
			Assert::AreEqual(matDatum.Size(), 0U);
			matDatum.PopBack();

			// Tests for tables
			Scope scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);
			Assert::AreEqual(scopeDatum.Size(), 1U);
			scopeDatum.PopBack();
			Assert::AreEqual(scopeDatum.Size(), 0U);
			scopeDatum.PopBack();
		}

		TEST_METHOD(Datum_Clear)
		{
			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);
			intDatum.Clear();
			Assert::IsTrue(intDatum.IsEmpty());

			intDatum.SetStorage(&intData, 1);
			auto intExpression = [&intDatum] { intDatum.Clear(); };
			Assert::ExpectException<std::exception>(intExpression);

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);
			floatDatum.Clear();
			Assert::IsTrue(floatDatum.IsEmpty());

			floatDatum.SetStorage(&floatData, 1);
			auto floatExpression = [&floatDatum] { floatDatum.Clear(); };
			Assert::ExpectException<std::exception>(floatExpression);

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);
			stringDatum.Clear();
			Assert::IsTrue(stringDatum.IsEmpty());

			stringDatum.SetStorage(&stringData, 1);
			auto stringExpression = [&stringDatum] { stringDatum.Clear(); };
			Assert::ExpectException<std::exception>(stringExpression);

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);
			vectorDatum.Clear();
			Assert::IsTrue(vectorDatum.IsEmpty());

			vectorDatum.SetStorage(&vecData, 1);
			auto vecExpression = [&vectorDatum] { vectorDatum.Clear(); };
			Assert::ExpectException<std::exception>(vecExpression);

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);
			matDatum.Clear();
			Assert::IsTrue(matDatum.IsEmpty());

			matDatum.SetStorage(&matData, 1);
			auto matExpression = [&matDatum] { matDatum.Clear(); };
			Assert::ExpectException<std::exception>(matExpression);

			// Tests for tables
			Scope scope;
			Scope* scopePtr = &scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);
			scopeDatum.Clear();
			Assert::IsTrue(scopeDatum.IsEmpty());

			scopeDatum.SetStorage(&scopePtr, 1);
			auto scopeExpression = [&scopeDatum] { scopeDatum.Clear(); };
			Assert::ExpectException<std::exception>(scopeExpression);

		}

		TEST_METHOD(Datum_ClearAndFree)
		{
			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.ClearAndFree();
			intDatum.PushBack(intData);
			intDatum.ClearAndFree();
			Assert::IsTrue(intDatum.IsEmpty());

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.ClearAndFree();
			floatDatum.PushBack(floatData);
			floatDatum.ClearAndFree();
			Assert::IsTrue(floatDatum.IsEmpty());

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.ClearAndFree();
			stringDatum.PushBack(stringData);
			stringDatum.ClearAndFree();
			Assert::IsTrue(stringDatum.IsEmpty());

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.ClearAndFree();
			vectorDatum.PushBack(vecData);
			vectorDatum.ClearAndFree();
			Assert::IsTrue(vectorDatum.IsEmpty());

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.ClearAndFree();
			matDatum.PushBack(matData);
			matDatum.ClearAndFree();
			Assert::IsTrue(matDatum.IsEmpty());

			// Tests for tables
			Scope scope;
			Datum scopeDatum;
			scopeDatum.ClearAndFree();
			scopeDatum.PushBack(&scope);
			scopeDatum.ClearAndFree();
			Assert::IsTrue(scopeDatum.IsEmpty());
		}
		
		TEST_METHOD(Datum_Set)
		{
			Datum pointerDatum;
			pointerDatum.SetType(DatumType::PointerType);

			// Tests for integers
			std::int32_t intData = 10, intData2 = 20;
			
			auto intExpression = [&pointerDatum, &intData] { pointerDatum.Set(intData); };
			Assert::ExpectException<std::exception>(intExpression);

			Datum intDatum;
			intDatum.PushBack(intData);
			Assert::IsTrue(intData == intDatum.Get<std::int32_t>());
			intDatum.Set(intData2);
			Assert::IsTrue(intData2 == intDatum.Get<std::int32_t>());


			intDatum.SetStorage(&intData, 1);
			auto intExpression2 = [&intDatum, &intData] { intDatum.Set(intData, 1); };
			Assert::ExpectException<std::exception>(intExpression2);

			// Tests for floats
			std::float_t floatData = 10.0f, floatData2 = 20.0f;

			auto floatExpression = [&pointerDatum, &floatData] { pointerDatum.Set(floatData); };
			Assert::ExpectException<std::exception>(floatExpression);

			Datum floatDatum;
			floatDatum.PushBack(floatData);
			Assert::IsTrue(floatData == floatDatum.Get<std::float_t>());
			floatDatum.Set(floatData2);
			Assert::IsTrue(floatData2 == floatDatum.Get<std::float_t>());

			floatDatum.SetStorage(&floatData, 1);
			auto floatExpression2 = [&floatDatum, &floatData] { floatDatum.Set(floatData, 1); };
			Assert::ExpectException<std::exception>(floatExpression2);

			// Tests for strings
			std::string stringData("str"), stringData2("str2");

			auto stringExpression = [&pointerDatum, &stringData] { pointerDatum.Set(stringData); };
			Assert::ExpectException<std::exception>(stringExpression);

			Datum stringDatum;
			stringDatum.PushBack(stringData);
			Assert::IsTrue(stringData == stringDatum.Get<std::string>());
			stringDatum.Set(stringData2);
			Assert::IsTrue(stringData2 == stringDatum.Get<std::string>());

			stringDatum.SetStorage(&stringData, 1);
			auto stringExpression2 = [&stringDatum, &stringData] { stringDatum.Set(stringData, 1); };
			Assert::ExpectException<std::exception>(stringExpression2);

			// Tests for vectors
			glm::vec4 vecData(1.0f), vecData2(2.0f);

			auto vecExpression = [&pointerDatum, &vecData] { pointerDatum.Set(vecData); };
			Assert::ExpectException<std::exception>(vecExpression);

			Datum vectorDatum;
			vectorDatum.PushBack(vecData);
			Assert::IsTrue(vecData == vectorDatum.Get<glm::vec4>());
			vectorDatum.Set(vecData2);
			Assert::IsTrue(vecData2 == vectorDatum.Get<glm::vec4>());

			vectorDatum.SetStorage(&vecData, 1);
			auto vecExpression2 = [&vectorDatum, &vecData] { vectorDatum.Set(vecData, 1); };
			Assert::ExpectException<std::exception>(vecExpression2);

			// Tests for matrices
			glm::mat4x4 matData, matData2(vecData, vecData, vecData, vecData);

			auto matExpression = [&pointerDatum, &matData] { pointerDatum.Set(matData); };
			Assert::ExpectException<std::exception>(matExpression);

			Datum matDatum;
			matDatum.PushBack(matData);
			Assert::IsTrue(matData == matDatum.Get<glm::mat4x4>());
			matDatum.Set(matData2);
			Assert::IsTrue(matData2 == matDatum.Get<glm::mat4x4>());

			matDatum.SetStorage(&matData, 1);
			auto matExpression2 = [&matDatum, &matData] { matDatum.Set(matData, 1); };
			Assert::ExpectException<std::exception>(matExpression2);
			
			// Tests for tables
			Scope scope, scope2;
			scope2["IntegerData"] = 10;
			Scope* scopePtr = &scope;

			auto scopeExpression = [&pointerDatum, &scope] { pointerDatum.Set(&scope); };
			Assert::ExpectException<std::exception>(scopeExpression);

			Datum scopeDatum;
			scopeDatum.PushBack(&scope);
			Assert::IsTrue(&scope == scopeDatum.Get<Scope*>());
			scopeDatum.Set(&scope2);
			Assert::IsTrue(&scope2 == scopeDatum.Get<Scope*>());

			scopeDatum.SetStorage(&scopePtr, 1);
			auto scopeExpression2 = [&scopeDatum, &scope] { scopeDatum.Set(&scope, 1); };
			Assert::ExpectException<std::exception>(scopeExpression2);

		}

		TEST_METHOD(Datum_Get)
		{
			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;

			auto intExpression = [&intDatum] { intDatum.Get<std::int32_t>(); };
			Assert::ExpectException<std::exception>(intExpression);

			intDatum.PushBack(intData);
			Assert::AreEqual(intData, intDatum.Get<std::int32_t>());

			const Datum intDatum2(intDatum);
			Assert::AreEqual(intData, intDatum2.Get<std::int32_t>());

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;

			auto floatExpression = [&floatDatum] { floatDatum.Get<std::float_t>(); };
			Assert::ExpectException<std::exception>(floatExpression);

			floatDatum.PushBack(floatData);
			Assert::AreEqual(floatData, floatDatum.Get<std::float_t>());

			const Datum floatDatum2(floatDatum);
			Assert::AreEqual(floatData, floatDatum2.Get<std::float_t>());

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;

			auto stringExpression = [&stringDatum] { stringDatum.Get<std::string>(); };
			Assert::ExpectException<std::exception>(stringExpression);

			stringDatum.PushBack(stringData);
			Assert::AreEqual(stringData, stringDatum.Get<std::string>());

			const Datum stringDatum2(stringDatum);
			Assert::AreEqual(stringData, stringDatum2.Get<std::string>());


			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;

			auto vecExpression = [&vectorDatum] { vectorDatum.Get<glm::vec4>(); };
			Assert::ExpectException<std::exception>(vecExpression);

			vectorDatum.PushBack(vecData);
			Assert::IsTrue(vecData == vectorDatum.Get<glm::vec4>());

			const Datum vectorDatum2(vectorDatum);
			Assert::IsTrue(vecData == vectorDatum2.Get<glm::vec4>());

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;

			auto matExpression = [&matDatum] { matDatum.Get<glm::mat4x4>(); };
			Assert::ExpectException<std::exception>(matExpression);

			matDatum.PushBack(matData);
			Assert::IsTrue(matData == matDatum.Get<glm::mat4x4>());
		
			const Datum matDatum2(matDatum);
			Assert::IsTrue(matData == matDatum2.Get<glm::mat4x4>());

			// Tests for tables
			Scope scope;
			Datum scopeDatum;

			auto scopeExpression = [&scopeDatum] { scopeDatum.Get<Scope*>(); };
			Assert::ExpectException<std::exception>(scopeExpression);

			scopeDatum.PushBack(&scope);
			Assert::IsTrue(&scope == scopeDatum.Get<Scope*>());

			const Datum scopeDatum2(scopeDatum);
			Assert::IsTrue(&scope == scopeDatum2.Get<Scope*>());
		}
		
		TEST_METHOD(Datum_Equals_Operator)
		{
			Datum unknownDatum;
			Datum pointerDatum;
			pointerDatum.SetType(DatumType::PointerType);

			// Tests for integers
			std::int32_t intData = 10, intData2 = 20;

			Datum intDatum, intDatum2;
			intDatum.SetType(DatumType::IntegerType);
			intDatum2.SetType(DatumType::IntegerType);

			Assert::IsFalse(intDatum == unknownDatum);
			Assert::IsFalse(intDatum == pointerDatum);
			
			Assert::IsTrue(intDatum == intDatum2);

			intDatum.PushBack(intData);
			intDatum2.PushBack(intData2);
			Assert::IsFalse(intDatum == intDatum2);
			intDatum2.Set(intData);
			Assert::IsTrue(intDatum == intDatum2);

			// Tests for floats
			std::float_t floatData = 10.0f, floatData2 = 20.0f;

			Datum floatDatum, floatDatum2;
			floatDatum.SetType(DatumType::FloatType);
			floatDatum2.SetType(DatumType::FloatType);

			Assert::IsFalse(floatDatum == unknownDatum);
			Assert::IsFalse(floatDatum == pointerDatum);

			Assert::IsTrue(floatDatum == floatDatum2);

			floatDatum.PushBack(floatData);
			floatDatum2.PushBack(floatData2);
			Assert::IsFalse(floatDatum == floatDatum2);
			floatDatum2.Set(floatData);
			Assert::IsTrue(floatDatum == floatDatum2);

			// Tests for strings
			std::string stringData("str"), stringData2("str2");

			Datum stringDatum, stringDatum2;
			stringDatum.SetType(DatumType::StringType);
			stringDatum2.SetType(DatumType::StringType);

			Assert::IsFalse(stringDatum == unknownDatum);
			Assert::IsFalse(stringDatum == pointerDatum);

			Assert::IsTrue(stringDatum == stringDatum2);

			stringDatum.PushBack(stringData);
			stringDatum2.PushBack(stringData2);
			Assert::IsFalse(stringDatum == stringDatum2);
			stringDatum2.Set(stringData);
			Assert::IsTrue(stringDatum == stringDatum2);

			// Tests for vectors
			glm::vec4 vecData(1.0f), vecData2(2.0f);

			Datum vecDatum, vecDatum2;
			vecDatum.SetType(DatumType::VectorType);
			vecDatum2.SetType(DatumType::VectorType);

			Assert::IsFalse(vecDatum == unknownDatum);
			Assert::IsFalse(vecDatum == pointerDatum);

			Assert::IsTrue(vecDatum == vecDatum2);

			vecDatum.PushBack(vecData);
			vecDatum2.PushBack(vecData2);
			Assert::IsFalse(vecDatum == vecDatum2);
			vecDatum2.Set(vecData);
			Assert::IsTrue(vecDatum == vecDatum2);

			// Tests for matrices
			glm::mat4x4 matData, matData2(vecData, vecData, vecData, vecData);

			Datum matDatum, matDatum2;
			matDatum.SetType(DatumType::MatrixType);
			matDatum2.SetType(DatumType::MatrixType);

			Assert::IsFalse(matDatum == unknownDatum);
			Assert::IsFalse(matDatum == pointerDatum);

			Assert::IsTrue(matDatum == matDatum2);

			matDatum.PushBack(matData);
			matDatum2.PushBack(matData2);
			Assert::IsFalse(matDatum == matDatum2);
			matDatum2.Set(matData);
			Assert::IsTrue(matDatum == matDatum2);

			// Tests for table
			Scope scope, scope2;
			scope["IntegerData"] = 10;

			Datum scopeDatum, scopeDatum2;
			scopeDatum.SetType(DatumType::TableType);
			scopeDatum2.SetType(DatumType::TableType);

			Assert::IsFalse(scopeDatum == unknownDatum);
			Assert::IsFalse(scopeDatum == pointerDatum);

			Assert::IsTrue(scopeDatum == scopeDatum2);

			scopeDatum.PushBack(&scope);
			scopeDatum2.PushBack(&scope2);
			Assert::IsFalse(scopeDatum == scopeDatum2);
			scopeDatum2.Set(&scope);
			Assert::IsTrue(scopeDatum == scopeDatum2);
		}

		TEST_METHOD(Datum_Inequals_Operator)
		{
			Datum unknownDatum;
			Datum pointerDatum;
			pointerDatum.SetType(DatumType::PointerType);

			// Tests for integers
			std::int32_t intData = 10, intData2 = 20;

			Datum intDatum, intDatum2;
			intDatum.SetType(DatumType::IntegerType);
			intDatum2.SetType(DatumType::IntegerType);

			Assert::IsTrue(intDatum != unknownDatum);
			Assert::IsTrue(intDatum != pointerDatum);
			
			Assert::IsFalse(intDatum != intDatum2);

			intDatum.PushBack(intData);
			intDatum2.PushBack(intData2);
			Assert::IsTrue(intDatum != intDatum2);
			intDatum2.Set(intData);
			Assert::IsFalse(intDatum != intDatum2);

			// Tests for floats
			std::float_t floatData = 10.0f, floatData2 = 20.0f;

			Datum floatDatum, floatDatum2;
			floatDatum.SetType(DatumType::FloatType);
			floatDatum2.SetType(DatumType::FloatType);

			Assert::IsTrue(floatDatum != unknownDatum);
			Assert::IsTrue(floatDatum != pointerDatum);

			Assert::IsFalse(floatDatum != floatDatum2);

			floatDatum.PushBack(floatData);
			floatDatum2.PushBack(floatData2);
			Assert::IsTrue(floatDatum != floatDatum2);
			floatDatum2.Set(floatData);
			Assert::IsFalse(floatDatum != floatDatum2);

			// Tests for strings
			std::string stringData("str"), stringData2("str2");

			Datum stringDatum, stringDatum2;
			stringDatum.SetType(DatumType::StringType);
			stringDatum2.SetType(DatumType::StringType);

			Assert::IsTrue(stringDatum != unknownDatum);
			Assert::IsTrue(stringDatum != pointerDatum);
			
			Assert::IsFalse(stringDatum != stringDatum2);

			stringDatum.PushBack(stringData);
			stringDatum2.PushBack(stringData2);
			Assert::IsTrue(stringDatum != stringDatum2);
			stringDatum2.Set(stringData);
			Assert::IsFalse(stringDatum != stringDatum2);

			// Tests for vectors
			glm::vec4 vecData(1.0f), vecData2(2.0f);

			Datum vecDatum, vecDatum2;
			vecDatum.SetType(DatumType::VectorType);
			vecDatum2.SetType(DatumType::VectorType);

			Assert::IsTrue(vecDatum != unknownDatum);
			Assert::IsTrue(vecDatum != pointerDatum);

			Assert::IsFalse(vecDatum != vecDatum2);

			vecDatum.PushBack(vecData);
			vecDatum2.PushBack(vecData2);
			Assert::IsTrue(vecDatum != vecDatum2);
			vecDatum2.Set(vecData);
			Assert::IsFalse(vecDatum != vecDatum2);

			// Tests for matrices
			glm::mat4x4 matData, matData2(vecData, vecData, vecData, vecData);

			Datum matDatum, matDatum2;
			matDatum.SetType(DatumType::MatrixType);
			matDatum2.SetType(DatumType::MatrixType);

			Assert::IsTrue(matDatum != unknownDatum);
			Assert::IsTrue(matDatum != pointerDatum);

			Assert::IsFalse(matDatum != matDatum2);

			matDatum.PushBack(matData);
			matDatum2.PushBack(matData2);
			Assert::IsTrue(matDatum != matDatum2);
			matDatum2.Set(matData);
			Assert::IsFalse(matDatum != matDatum2);

			// Tests for tables
			Scope scope, scope2;
			scope["IntegerData"] = 10;

			Datum scopeDatum, scopeDatum2;
			scopeDatum.SetType(DatumType::TableType);
			scopeDatum2.SetType(DatumType::TableType);

			Assert::IsTrue(scopeDatum != unknownDatum);
			Assert::IsTrue(scopeDatum != pointerDatum);

			Assert::IsFalse(scopeDatum != scopeDatum2);

			scopeDatum.PushBack(&scope);
			scopeDatum2.PushBack(&scope2);
			Assert::IsTrue(scopeDatum != scopeDatum2);
			scopeDatum2.Set(&scope);
			Assert::IsFalse(scopeDatum != scopeDatum2);
		}

		TEST_METHOD(Datum_Equals_Scalar_Operator)
		{
			Datum unknownDatum;

			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);

			Assert::IsFalse(unknownDatum == intData);
			Assert::IsTrue(intDatum == intData);

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);

			Assert::IsFalse(unknownDatum == floatData);
			Assert::IsTrue(floatDatum == floatData);

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);

			Assert::IsFalse(unknownDatum == stringData);
			Assert::IsTrue(stringDatum == stringData);

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);

			Assert::IsFalse(unknownDatum == vecData);
			Assert::IsTrue(vectorDatum == vecData);

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);

			Assert::IsFalse(unknownDatum == matData);
			Assert::IsTrue(matDatum == matData);

			// Tests for tables
			Scope scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);

			Assert::IsFalse(unknownDatum == &scope);
			Assert::IsTrue(scopeDatum == &scope);
		}

		TEST_METHOD(Datum_Inequals_Scalar_Operator)
		{
			Datum unknownDatum;

			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);

			Assert::IsTrue(unknownDatum != intData);
			Assert::IsFalse(intDatum != intData);

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);

			Assert::IsTrue(unknownDatum != floatData);
			Assert::IsFalse(floatDatum != floatData);

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);

			Assert::IsTrue(unknownDatum != stringData);
			Assert::IsFalse(stringDatum != stringData);

			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);

			Assert::IsTrue(unknownDatum != vecData);
			Assert::IsFalse(vectorDatum != vecData);

			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);

			Assert::IsTrue(unknownDatum != matData);
			Assert::IsFalse(matDatum != matData);

			// Tests for tables
			Scope scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);

			Assert::IsTrue(unknownDatum != &scope);
			Assert::IsFalse(scopeDatum != &scope);
		}

		TEST_METHOD(Datum_SetStorage)
		{
			Datum unknownDatum;

			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);

			intDatum.SetStorage(&intData, 1);

			auto intExpression = [&unknownDatum, &intData] { unknownDatum.SetStorage(&intData, 1); };
			Assert::ExpectException<std::exception>(intExpression);

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);

			floatDatum.SetStorage(&floatData, 1);

			auto floatExpression = [&unknownDatum, &floatData] { unknownDatum.SetStorage(&floatData, 1); };
			Assert::ExpectException<std::exception>(floatExpression);

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);

			stringDatum.SetStorage(&stringData, 1);

			auto strExpression = [&unknownDatum, &stringData] { unknownDatum.SetStorage(&stringData, 1); };
			Assert::ExpectException<std::exception>(strExpression);


			// Tests for vectors
			glm::vec4 vecData(1.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);

			vectorDatum.SetStorage(&vecData, 1);

			auto vecExpression = [&unknownDatum, &vecData] { unknownDatum.SetStorage(&vecData, 1); };
			Assert::ExpectException<std::exception>(vecExpression);


			// Tests for matrices
			glm::mat4x4 matData;
			Datum matDatum;
			matDatum.PushBack(matData);

			matDatum.SetStorage(&matData, 1);

			auto matExpression = [&unknownDatum, &matData] { unknownDatum.SetStorage(&matData, 1); };
			Assert::ExpectException<std::exception>(matExpression);

			// Tests for tables
			Scope scope;
			Scope* scopePtr = &scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);

			scopeDatum.SetStorage(&scopePtr, 1);

			auto scopeExpression = [&unknownDatum, &scopePtr] { unknownDatum.SetStorage(&scopePtr, 1); };
			Assert::ExpectException<std::exception>(scopeExpression);
		}

		TEST_METHOD(Datum_ToString)
		{
			Datum unknownDatum;
			auto expression = [&unknownDatum] { unknownDatum.ToString(); };
			Assert::ExpectException<std::exception>(expression);

			// Tests for integers
			std::int32_t intData = 10;
			Datum intDatum;
			intDatum.PushBack(intData);
			Assert::AreEqual(intDatum.ToString(), std::to_string(intData));

			// Tests for floats
			std::float_t floatData = 10.0f;
			Datum floatDatum;
			floatDatum.PushBack(floatData);
			Assert::AreEqual(floatDatum.ToString(), std::to_string(floatData));

			// Tests for strings
			std::string stringData = "str";
			Datum stringDatum;
			stringDatum.PushBack(stringData);
			Assert::AreEqual(stringDatum.ToString(), stringData);

			// Tests for vectors
			glm::vec4 vecData(1.0f, 2.0f, 3.0f, 4.0f);
			Datum vectorDatum;
			vectorDatum.PushBack(vecData);
			Assert::AreEqual(vectorDatum.ToString(), glm::to_string(vecData));

			// Tests for matrices
			glm::mat4x4 matData(vecData, vecData, vecData, vecData);
			Datum matDatum;
			matDatum.PushBack(matData);
			Assert::AreEqual(matDatum.ToString(), glm::to_string(matData));

			// Tests for tables
			Scope scope;
			Datum scopeDatum;
			scopeDatum.PushBack(&scope);
			Assert::IsTrue(scopeDatum.ToString() == "Scope(0)");
		}

		TEST_METHOD(Datum_SetFromString)
		{
			Datum unknownDatum;
			std::string str("str");
			auto expression = [&unknownDatum, &str] { unknownDatum.SetFromString(str); };
			Assert::ExpectException<std::exception>(expression);

			// Tests for integers
			std::int32_t intData = 10, intData2 = 20;
			std::string intStr = "20";
			Datum intDatum;
			intDatum.PushBack(intData);
			
			Assert::AreNotEqual(intData2, intDatum.Get<std::int32_t>());
			Assert::IsTrue(intDatum.SetFromString(intStr));
			Assert::AreEqual(intData2, intDatum.Get<std::int32_t>());

			// Tests for floats
			std::float_t floatData = 10.0f, floatData2 = 20.0f;
			std::string floatStr = "20.0";
			Datum floatDatum;
			floatDatum.PushBack(floatData);
			
			Assert::AreNotEqual(floatData2, floatDatum.Get<std::float_t>());
			Assert::IsTrue(floatDatum.SetFromString(floatStr));
			Assert::AreEqual(floatData2, floatDatum.Get<std::float_t>());

			// Tests for strings
			std::string stringData = "str", stringData2 = "str2";
			Datum stringDatum;
			stringDatum.PushBack(stringData2);
			
			Assert::AreNotEqual(stringData, stringDatum.Get<std::string>());
			Assert::IsTrue(stringDatum.SetFromString(stringData));
			Assert::AreEqual(stringData, stringDatum.Get<std::string>());

			// Tests for vectors
			glm::vec4 vecData(1.0f, 2.0f, 3.0f, 4.0f), vecData2(2.0f, 3.0f, 4.0f, 5.0f);
			std::string vecString("vec4(1.0,2.0,3.0,4.0)");
			Datum vectorDatum;
			vectorDatum.PushBack(vecData2);
			
			Assert::IsFalse(vecData == vectorDatum.Get<glm::vec4>());
			Assert::IsTrue(vectorDatum.SetFromString(vecString));
			Assert::IsTrue(vecData == vectorDatum.Get<glm::vec4>());

			// Tests for matrices
			glm::mat4x4 matData(vecData, vecData, vecData, vecData2), matData2(vecData2, vecData2, vecData2, vecData);
			std::string matString("mat4x4((1.0,2.0,3.0,4.0),(1.0,2.0,3.0,4.0),(1.0,2.0,3.0,4.0),(2.0,3.0,4.0,5.0))");
			Datum matDatum;
			matDatum.PushBack(matData2);
			
			Assert::IsFalse(matData == matDatum.Get<glm::mat4x4>());
			Assert::IsTrue(matDatum.SetFromString(matString));
			Assert::IsTrue(matData == matDatum.Get<glm::mat4x4>());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}