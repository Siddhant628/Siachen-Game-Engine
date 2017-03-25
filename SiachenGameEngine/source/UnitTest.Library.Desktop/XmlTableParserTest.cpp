#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "XmlSharedDataTable.h"
#include "RTTI.h"

#include "Scope.h"

#include "XmlParseHelperTable.h"
#include "XmlParseHelperPrimitives.h"
#include "XmlParseHelperMath.h"

#include "SampleXmlSharedData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlTableParserTest)
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

		TEST_METHOD(XmlTableParser_Primitives)
		{
			XmlSharedDataTable sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperTable tableHelper;
			XmlParseHelperPrimitives primitiveHelper;
			parseMaster.AddHelper(tableHelper);
			parseMaster.AddHelper(primitiveHelper);

			parseMaster.ParseFromFile("../../../XmlWithTable.xml");

			// Test for integers
			std::int32_t int1 = (*sharedData.mScope)["Child1"][0]["Int1"].Get<std::int32_t>();
			Assert::AreEqual(int1, 10);
			std::int32_t intArray1 = (*sharedData.mScope)["Child2"][0]["IntArray"].Get<std::int32_t>();
			Assert::AreEqual(intArray1, 20);
			std::int32_t intArray2 = (*sharedData.mScope)["Child2"][0]["IntArray"].Get<std::int32_t>(1);
			Assert::AreEqual(intArray2, 30);
			std::int32_t int2 = (*sharedData.mScope)["Child2"][1]["Int2"].Get<std::int32_t>();
			Assert::AreEqual(int2, 40);

			// Test for floats
			std::float_t floatArray1 = (*sharedData.mScope)["FloatArray"].Get<std::float_t>();
			Assert::AreEqual(floatArray1, 1.5f);
			std::float_t floatArray2 = (*sharedData.mScope)["FloatArray"].Get<std::float_t>(1);
			Assert::AreEqual(floatArray2, 2.5f);
			std::float_t float1 = (*sharedData.mScope)["Child2"][0]["FloatValue"].Get<std::float_t>();
			Assert::AreEqual(float1, 1.5f);
			std::float_t float2 = (*sharedData.mScope)["Child2"][1]["FloatValue"].Get<std::float_t>();
			Assert::AreEqual(float2, 2.5f);

			// Test for strings
			std::string stringValue1 = (*sharedData.mScope)["Child1"][0]["String1"].Get<std::string>();
			Assert::IsTrue(stringValue1 == "One");
			std::string stringValue2 = (*sharedData.mScope)["Child2"][1]["StringArray"].Get<std::string>();
			Assert::IsTrue(stringValue2 == "Two");
			std::string stringValue3 = (*sharedData.mScope)["Child2"][1]["StringArray"].Get<std::string>(1);
			Assert::IsTrue(stringValue3 == "Three");
		}

		TEST_METHOD(XmlTableParser_Math)
		{
			XmlSharedDataTable sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperTable tableHelper;
			XmlParseHelperPrimitives primitiveHelper;
			XmlParseHelperMath mathHelper;

			parseMaster.AddHelper(tableHelper);
			parseMaster.AddHelper(primitiveHelper);
			parseMaster.AddHelper(mathHelper);

			parseMaster.ParseFromFile("../../../XmlWithTable.xml");

			// Test for vectors
			glm::vec4 vec1 = (*sharedData.mScope)["Vector1"].Get<glm::vec4>();
			Assert::IsTrue(vec1 == glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			glm::vec4 vecArray1 = (*sharedData.mScope)["Child2"][1]["VectorArray"].Get<glm::vec4>();
			Assert::IsTrue(vecArray1 == glm::vec4(1.0f, 2.0f, 3.0f, 0.0f));
			glm::vec4 vecArray2 = (*sharedData.mScope)["Child2"][1]["VectorArray"].Get<glm::vec4>(1);
			Assert::IsTrue(vecArray2 == glm::vec4(2.0f, 2.0f, 3.0f, 0.0f));

			// Test for matrices
			glm::mat4x4 mat1(vec1, vec1, vec1, vec1);
			glm::mat4x4 mat2(vecArray1, vecArray1, vecArray1, vecArray1);
			Assert::IsTrue((*sharedData.mScope)["MatrixArray"].Get<glm::mat4x4>() == mat1);
			Assert::IsTrue((*sharedData.mScope)["MatrixArray"].Get<glm::mat4x4>(1) == mat2);
		}

		TEST_METHOD(XmlTableParser_Cloning)
		{
			XmlSharedDataTable originalSharedData;
			XmlParseMaster parseMaster(originalSharedData);

			XmlParseHelperTable tableHelper;
			XmlParseHelperPrimitives primitiveHelper;
			XmlParseHelperMath mathHelper;

			parseMaster.AddHelper(tableHelper);
			parseMaster.AddHelper(primitiveHelper);
			parseMaster.AddHelper(mathHelper);

			parseMaster.ParseFromFile("../../../XmlWithTable.xml");

			XmlParseMaster* clonedParseMaster = parseMaster.Clone();

			clonedParseMaster->ParseFromFile("../../../XmlWithTable.xml");

			//Random tests
			XmlSharedDataTable& sharedData = *(reinterpret_cast<XmlSharedDataTable*>(clonedParseMaster->GetSharedData()));

			std::int32_t int1 = (*sharedData.mScope)["Child1"][0]["Int1"].Get<std::int32_t>();
			Assert::AreEqual(int1, 10);
			std::float_t floatArray2 = (*sharedData.mScope)["FloatArray"].Get<std::float_t>(1);
			Assert::AreEqual(floatArray2, 2.5f);
			std::string stringValue3 = (*sharedData.mScope)["Child2"][1]["StringArray"].Get<std::string>(1);
			Assert::IsTrue(stringValue3 == "Three");

			glm::vec4 vec1 = (*sharedData.mScope)["Vector1"].Get<glm::vec4>();
			Assert::IsTrue(vec1 == glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			glm::vec4 vecArray1 = (*sharedData.mScope)["Child2"][1]["VectorArray"].Get<glm::vec4>();
			Assert::IsTrue(vecArray1 == glm::vec4(1.0f, 2.0f, 3.0f, 0.0f));
			glm::vec4 vecArray2 = (*sharedData.mScope)["Child2"][1]["VectorArray"].Get<glm::vec4>(1);
			Assert::IsTrue(vecArray2 == glm::vec4(2.0f, 2.0f, 3.0f, 0.0f));

			glm::mat4x4 mat1(vec1, vec1, vec1, vec1);
			glm::mat4x4 mat2(vecArray1, vecArray1, vecArray1, vecArray1);
			Assert::IsTrue((*sharedData.mScope)["MatrixArray"].Get<glm::mat4x4>() == mat1);
			Assert::IsTrue((*sharedData.mScope)["MatrixArray"].Get<glm::mat4x4>(1) == mat2);

			delete clonedParseMaster;
		}

		TEST_METHOD(XmlTableParser_Initialize)
		{
			XmlSharedDataTable sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperTable tableHelper;
			XmlParseHelperPrimitives primitiveHelper;
			XmlParseHelperMath mathHelper;

			SiachenGameEngine::HelperClasses::SampleXmlSharedData someSharedData;

			auto initExpression = [&tableHelper, &someSharedData] {tableHelper.Initialize(someSharedData); };
			Assert::ExpectException<std::runtime_error>(initExpression);

			auto initExpression2 = [&primitiveHelper, &someSharedData] {primitiveHelper.Initialize(someSharedData); };
			Assert::ExpectException<std::runtime_error>(initExpression2);

			auto initExpression3 = [&mathHelper, &someSharedData] {mathHelper.Initialize(someSharedData); };
			Assert::ExpectException<std::runtime_error>(initExpression3);

		}

		TEST_METHOD(XmlTableParser_RTTI)
		{
			RTTI* sharedDataTable = new XmlSharedDataTable();
			RTTI* sharedDataSample = new SiachenGameEngine::HelperClasses::SampleXmlSharedData();

			Assert::IsTrue(sharedDataTable->Is("XmlSharedDataTable"));
			Assert::IsFalse(sharedDataSample->Is("XmlSharedDataTable"));

			Assert::IsTrue(sharedDataTable->Is(XmlSharedDataTable::TypeIdClass()));
			Assert::IsFalse(sharedDataSample->Is(XmlSharedDataTable::TypeIdClass()));

			Assert::IsNotNull(sharedDataTable->As<XmlSharedDataTable>());
			Assert::IsNull(sharedDataSample->As<XmlSharedDataTable>());

			Assert::IsNotNull(sharedDataTable->QueryInterface(XmlSharedDataTable::TypeIdClass()));
			Assert::IsNull(sharedDataSample->QueryInterface(XmlSharedDataTable::TypeIdClass()));

			delete sharedDataTable;
			delete sharedDataSample;
		}

		TEST_METHOD(XmlTableParser_Invalid)
		{
			XmlSharedDataTable sharedData;
			XmlParseMaster parseMaster(sharedData);

			XmlParseHelperTable tableHelper;
			XmlParseHelperPrimitives primitiveHelper;
			XmlParseHelperMath mathHelper;

			parseMaster.AddHelper(tableHelper);
			parseMaster.AddHelper(primitiveHelper);
			parseMaster.AddHelper(mathHelper);

			parseMaster.ParseFromFile("../../../XmlWithTableInvalid.xml");

			// Invalid entries as strings
			Assert::AreEqual((*sharedData.mScope)["InvalidVector"].Size(), 0U);
			Assert::AreEqual((*sharedData.mScope)["InvalidMatrix"].Size(), 0U);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlTableParserTest::sStartMemState;
}