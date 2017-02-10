#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::HelperClasses;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<HashMap<std::int32_t, std::int32_t>::Iterator>(typename const HashMap<std::int32_t, std::int32_t>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					bufferStream << "HashMap_IntegerKey_Iterator_" << (*it).second;
				}
				catch (std::exception) {}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<HashMap<char*, std::int32_t>::Iterator>(typename const HashMap<char*, std::int32_t>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					bufferStream << "HashMap_Char*Key_Iterator_" << (*it).second;
				}
				catch (std::exception) {}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<HashMap<std::string, std::int32_t>::Iterator>(typename const HashMap<std::string, std::int32_t>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					bufferStream << "HashMap_StringKey_Iterator_" << (*it).second;
				}
				catch (std::exception) {}
				return bufferStream.str();
			}

			template<>
			std::wstring ToString<HashMap<Foo, std::int32_t>::Iterator>(typename const HashMap<Foo, std::int32_t>::Iterator& it)
			{
				std::wstringstream bufferStream;
				try
				{
					bufferStream << "HashMap_FooKey_Iterator_" << (*it).second;
				}
				catch (std::exception) {}
				return bufferStream.str();
			}
		}
	}
}

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashMapTest)
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

		TEST_METHOD(Default_Hash_Functor)
		{
			// Default hash function
			DefaultHash<std::int32_t> intHash;
			std::uint32_t a = 1000, b = 1000;
			Assert::AreEqual(intHash(a), intHash(b));

			// Specialization for string keys
			DefaultHash<std::string> stringHash;
			std::string str = "Hey";
			std::string str2 = str;
			Assert::AreEqual(stringHash(str), stringHash(str2));

			// Specialization for char*
			DefaultHash<char*> charHash;
			char* str3 = "Hey";
			char* str4 = "yeH";
			Assert::AreEqual(charHash(str3), charHash(str4));

			// Specialization for Foo
			DefaultHash<Foo> fooHash;
			Foo foo(a), foo2(b);
			Assert::AreEqual(fooHash(foo), fooHash(foo2));
		}

		TEST_METHOD(Default_Compare_Functor)
		{
			std::int32_t data = 10, data2 = 10, data3 = 20;

			// Comparison of integers
			DefaultCompareFunctor<std::int32_t> intFuctor;
			Assert::IsTrue(intFuctor(data, data2));
			Assert::IsFalse(intFuctor(data, data3));

			// Comparison of strings
			DefaultCompareFunctor<std::string> stringFunctor;
			std::string str = "Hey";
			std::string str2 = str;
			Assert::IsTrue(stringFunctor(str, str2));
			str2 = "neh";
			Assert::IsFalse(stringFunctor(str, str2));

			// Comparison of char*
			DefaultCompareFunctor<char*> charPtrFunctor;
			char* str3 = "Hey";
			char str4[4];
			Assert::IsFalse(charPtrFunctor(str3, str4));
			strcpy_s(str4, str3);
			Assert::IsTrue(charPtrFunctor(str3, str4));

			// Comparison of Foos
			Foo foo(data), foo2(data2), foo3(data3);
			DefaultCompareFunctor<Foo> fooFunctor;
			Assert::IsTrue(fooFunctor(foo, foo2));
			Assert::IsFalse(fooFunctor(foo, foo3));
		}

		TEST_METHOD(HashMap_Insert)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			intMap.Insert(p1);
			Assert::AreEqual(1U, intMap.Size());
			intMap.Insert(p1);
			Assert::AreEqual(1U, intMap.Size());
			Assert::IsTrue(intMap.ContainsKey(data));

			intMap.Insert(p2);
			Assert::AreEqual(2U, intMap.Size());
			intMap.Insert(p2);
			Assert::AreEqual(2U, intMap.Size());
			Assert::IsTrue(intMap.ContainsKey(data2));

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey", *b = "yeh", *c = "zed";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2), char3(c, data);

			charPtrMap.Insert(char1);
			Assert::AreEqual(1U, charPtrMap.Size());
			charPtrMap.Insert(char1);
			Assert::AreEqual(1U, charPtrMap.Size());
			Assert::IsTrue(charPtrMap.ContainsKey(a));

			charPtrMap.Insert(char2);
			Assert::AreEqual(2U, charPtrMap.Size());
			charPtrMap.Insert(char2);
			Assert::AreEqual(2U, charPtrMap.Size());
			Assert::IsTrue(charPtrMap.ContainsKey(b));

			charPtrMap.Insert(char3);
			Assert::AreEqual(3U, charPtrMap.Size());
			charPtrMap.Insert(char3);
			Assert::AreEqual(3U, charPtrMap.Size());
			Assert::IsTrue(charPtrMap.ContainsKey(c));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war", f = "dog";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2), str3(f, data);

			stringMap.Insert(str);
			Assert::AreEqual(1U, stringMap.Size());
			stringMap.Insert(str);
			Assert::AreEqual(1U, stringMap.Size());
			Assert::IsTrue(stringMap.ContainsKey(d));

			stringMap.Insert(str2);
			Assert::AreEqual(2U, stringMap.Size());
			stringMap.Insert(str2);
			Assert::AreEqual(2U, stringMap.Size());
			Assert::IsTrue(stringMap.ContainsKey(e));

			stringMap.Insert(str3);
			Assert::AreEqual(3U, stringMap.Size());
			stringMap.Insert(str3);
			Assert::AreEqual(3U, stringMap.Size());
			Assert::IsTrue(stringMap.ContainsKey(f));
			
			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			fooMap.Insert(foo);
			Assert::AreEqual(1U, fooMap.Size());
			fooMap.Insert(foo);
			Assert::AreEqual(1U, fooMap.Size());
			Assert::IsTrue(fooMap.ContainsKey(g));

			fooMap.Insert(foo2);
			Assert::AreEqual(2U, fooMap.Size());
			fooMap.Insert(foo2);
			Assert::AreEqual(2U, fooMap.Size());
			Assert::IsTrue(fooMap.ContainsKey(h));
		}

		TEST_METHOD(HashMap_Find)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			Assert::AreEqual(intMap.end(), intMap.Find(data));
			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.Insert(p1);
			Assert::AreNotEqual(intMap.end(), intMap.Find(data));
			Assert::AreEqual(it, intMap.Find(data));

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);
			
			Assert::AreEqual(charPtrMap.end(), charPtrMap.Find(a));
			HashMap<char*, std::int32_t>::Iterator it2 = charPtrMap.Insert(char1);
			Assert::AreNotEqual(charPtrMap.end(), charPtrMap.Find(a));
			Assert::AreEqual(it2, charPtrMap.Find(a));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			Assert::AreEqual(stringMap.end(), stringMap.Find(d));
			HashMap<std::string, std::int32_t>::Iterator it3 = stringMap.Insert(str);
			Assert::AreNotEqual(stringMap.end(), stringMap.Find(d));
			Assert::AreEqual(it3, stringMap.Find(d));

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);
			
			Assert::AreEqual(fooMap.end(), fooMap.Find(g));
			HashMap<Foo, std::int32_t>::Iterator it4 = fooMap.Insert(foo);
			Assert::AreNotEqual(fooMap.end(), fooMap.Find(g));
			Assert::AreEqual(it4, fooMap.Find(g));
		}

		TEST_METHOD(HashMap_Remove)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			Assert::IsFalse(intMap.Remove(data));
			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.Insert(p1);
			Assert::AreEqual(1U, intMap.Size());
			Assert::IsTrue(intMap.Remove(data));
			Assert::AreEqual(0U, intMap.Size());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			Assert::IsFalse(charPtrMap.Remove(a));
			HashMap<char*, std::int32_t>::Iterator it2 = charPtrMap.Insert(char1);
			Assert::AreEqual(1U, charPtrMap.Size());
			Assert::IsTrue(charPtrMap.Remove(a));
			Assert::AreEqual(0U, charPtrMap.Size());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			Assert::IsFalse(stringMap.Remove(d));
			HashMap<std::string, std::int32_t>::Iterator it3 = stringMap.Insert(str);
			Assert::AreEqual(1U, stringMap.Size());
			Assert::IsTrue(stringMap.Remove(d));
			Assert::AreEqual(0U, stringMap.Size());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			Assert::IsFalse(fooMap.Remove(g));
			HashMap<Foo, std::int32_t>::Iterator it4 = fooMap.Insert(foo);
			Assert::AreEqual(1U, fooMap.Size());
			Assert::IsTrue(fooMap.Remove(g));
			Assert::AreEqual(0U, fooMap.Size());
		}

		TEST_METHOD(HashMap_Size)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			intMap.Insert(p1);
			Assert::AreEqual(1U, intMap.Size());
			intMap.Insert(p2);
			Assert::AreEqual(2U, intMap.Size());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey", *b = "yeh";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2);

			charPtrMap.Insert(char1);
			Assert::AreEqual(1U, charPtrMap.Size());
			charPtrMap.Insert(char2);
			Assert::AreEqual(2U, charPtrMap.Size());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2);

			stringMap.Insert(str);
			Assert::AreEqual(1U, stringMap.Size());
			stringMap.Insert(str2);
			Assert::AreEqual(2U, stringMap.Size());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			fooMap.Insert(foo);
			Assert::AreEqual(1U, fooMap.Size());
			fooMap.Insert(foo2);
			Assert::AreEqual(2U, fooMap.Size());

		}

		TEST_METHOD(HashMap_ContainsKey)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			Assert::IsFalse(intMap.ContainsKey(data));
			intMap.Insert(p1);
			Assert::IsTrue(intMap.ContainsKey(data));

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			Assert::IsFalse(charPtrMap.ContainsKey(a));
			charPtrMap.Insert(char1);
			Assert::IsTrue(charPtrMap.ContainsKey(a));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			Assert::IsFalse(stringMap.ContainsKey(d));
			stringMap.Insert(str);
			Assert::IsTrue(stringMap.ContainsKey(d));

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			Assert::IsFalse(fooMap.ContainsKey(g));
			fooMap.Insert(foo);
			Assert::IsTrue(fooMap.ContainsKey(g));
		}

		TEST_METHOD(HashMap_Copy_Constructor)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;
			
			intMap.Insert(p1);
			intMap.Insert(p2);
			HashMap<std::int32_t, std::int32_t> intMap2(intMap);
			Assert::IsTrue(intMap.ContainsKey(data));
			Assert::IsTrue(intMap.ContainsKey(data2));

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey", *b = "yeh";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2);

			charPtrMap.Insert(char1);
			charPtrMap.Insert(char2);
			HashMap<char*, std::int32_t> charPtrMap2(charPtrMap);
			Assert::IsTrue(charPtrMap2.ContainsKey(a));
			Assert::IsTrue(charPtrMap2.ContainsKey(b));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2);

			stringMap.Insert(str);
			stringMap.Insert(str2);
			HashMap <std::string , std::int32_t > stringMap2(stringMap);
			Assert::IsTrue(stringMap2.ContainsKey(d));
			Assert::IsTrue(stringMap2.ContainsKey(e));

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			fooMap.Insert(foo);
			fooMap.Insert(foo2);
			HashMap <Foo, std::int32_t > fooMap2(fooMap);
			Assert::IsTrue(fooMap2.ContainsKey(g));
			Assert::IsTrue(fooMap2.ContainsKey(h));
		}

		TEST_METHOD(HashMap_Clear)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			intMap.Insert(p1);
			Assert::IsTrue(intMap.ContainsKey(data));
			Assert::AreEqual(1U, intMap.Size());
			intMap.Insert(p1);
			intMap.Clear();
			Assert::AreEqual(0U, intMap.Size());
			Assert::IsFalse(intMap.ContainsKey(data));
			

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			charPtrMap.Insert(char1);
			Assert::IsTrue(charPtrMap.ContainsKey(a));
			Assert::AreEqual(1U, charPtrMap.Size());
			charPtrMap.Clear();
			Assert::AreEqual(0U, charPtrMap.Size());
			Assert::IsFalse(charPtrMap.ContainsKey(a));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			stringMap.Insert(str);
			Assert::IsTrue(stringMap.ContainsKey(d));
			Assert::AreEqual(1U, stringMap.Size());
			stringMap.Clear();
			Assert::AreEqual(0U, stringMap.Size());
			Assert::IsFalse(stringMap.ContainsKey(d));

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			fooMap.Insert(foo);
			Assert::IsTrue(fooMap.ContainsKey(g));
			Assert::AreEqual(1U, fooMap.Size());
			fooMap.Clear();
			Assert::AreEqual(0U, fooMap.Size());
			Assert::IsFalse(fooMap.ContainsKey(g));
		}

		TEST_METHOD(HashMap_Assignment_Operator)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap, intMap2;

			intMap.Insert(p1);
			intMap2.Insert(p2);
			intMap2 = intMap;
			Assert::IsTrue(intMap2.ContainsKey(data));
			Assert::IsFalse(intMap2.ContainsKey(data2));

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap, charPtrMap2;
			char* a = "hey", *b = "yeh", *c = "zed";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2), char3(c, data);

			charPtrMap.Insert(char1);
			charPtrMap.Insert(char2);
			charPtrMap2.Insert(char3);
			charPtrMap = charPtrMap2;
			Assert::AreEqual(1U, charPtrMap.Size());
			Assert::IsTrue(charPtrMap.ContainsKey(c));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap, stringMap2;
			std::string d = "raw", e = "war", f = "dog";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2), str3(f, data);

			stringMap.Insert(str);
			stringMap.Insert(str2);
			stringMap2.Insert(str3);
			stringMap = stringMap2;
			Assert::AreEqual(1U, stringMap.Size());
			Assert::IsTrue(stringMap.ContainsKey(f));

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap, fooMap2;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			fooMap.Insert(foo);
			fooMap2.Insert(foo2);
			fooMap2 = fooMap;
			Assert::IsTrue(fooMap2.ContainsKey(g));
			Assert::IsFalse(fooMap2.ContainsKey(h));
		}

		TEST_METHOD(HashMap_Subscript_Operator)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			intMap.Insert(p1);
			Assert::AreEqual(intMap[data], data2);
			Assert::AreEqual(std::int32_t(), intMap[data2]);
			Assert::IsTrue(intMap.ContainsKey(data2));

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey", *b = "yeh";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2);

			charPtrMap.Insert(char1);
			Assert::AreEqual(charPtrMap[a], data);
			Assert::AreEqual(std::int32_t(), charPtrMap[b]);
			Assert::IsTrue(charPtrMap.ContainsKey(b));

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war", f = "dog";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2), str3(f, data);

			stringMap.Insert(str);
			Assert::AreEqual(stringMap[d], data);
			Assert::AreEqual(std::int32_t(), stringMap[e]);
			Assert::IsTrue(stringMap.ContainsKey(e));

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			fooMap.Insert(foo);
			Assert::AreEqual(fooMap[g], data);
			Assert::AreEqual(std::int32_t(), fooMap[h]);
			Assert::IsTrue(fooMap.ContainsKey(h));
		}

		TEST_METHOD(HashMap_Subscript_Operator_Constant)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;
			const HashMap<std::int32_t, std::int32_t> intMap2;

			auto intExpression = [&intMap2, &data] { intMap2[data]; };
			Assert::ExpectException<std::exception>(intExpression);
			intMap.Insert(p1);
			const HashMap<std::int32_t, std::int32_t> intMap3(intMap);
			Assert::AreEqual(intMap3[data], data2);

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			const HashMap<char*, std::int32_t> charPtrMap2;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			auto charExpression = [&charPtrMap2, &a] { charPtrMap2[a]; };
			Assert::ExpectException<std::exception>(charExpression);
			charPtrMap.Insert(char1);
			const HashMap<char*, std::int32_t> charPtrMap3(charPtrMap);
			Assert::AreEqual(charPtrMap3[a], data);

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			const HashMap<std::string, std::int32_t> stringMap2;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			auto stringExpression = [&stringMap2, &d] { stringMap2[d]; };
			Assert::ExpectException<std::exception>(stringExpression);
			stringMap.Insert(str);
			const HashMap<std::string, std::int32_t> stringMap3(stringMap);
			Assert::AreEqual(stringMap3[d], data);

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			const HashMap<Foo, std::int32_t> fooMap2;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			auto fooExpression = [&fooMap2, &g] { fooMap2[g]; };
			Assert::ExpectException<std::exception>(fooExpression);
			fooMap.Insert(foo);
			const HashMap<Foo, std::int32_t> fooMap3(fooMap);
			Assert::AreEqual(fooMap3[g], data);
		}

		TEST_METHOD(HashMap_Begin)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			Assert::AreEqual(intMap.begin(), intMap.end());
			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.Insert(p1);
			Assert::AreNotEqual(intMap.begin(), intMap.end());
			Assert::AreEqual(it, intMap.begin());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			Assert::AreEqual(charPtrMap.begin(), charPtrMap.end());
			HashMap<char*, std::int32_t>::Iterator it2 = charPtrMap.Insert(char1);
			Assert::AreNotEqual(charPtrMap.begin(), charPtrMap.end());
			Assert::AreEqual(it2, charPtrMap.begin());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			Assert::AreEqual(stringMap.begin(), stringMap.end());
			HashMap<std::string, std::int32_t>::Iterator it3 = stringMap.Insert(str);
			Assert::AreNotEqual(stringMap.begin(), stringMap.end());
			Assert::AreEqual(it3, stringMap.begin());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			Assert::AreEqual(fooMap.begin(), fooMap.end());
			HashMap<Foo, std::int32_t>::Iterator it4 = fooMap.Insert(foo);
			Assert::AreNotEqual(fooMap.begin(), fooMap.end());
			Assert::AreEqual(it4, fooMap.begin());
		}

		TEST_METHOD(HashMap_End)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			Assert::AreEqual(intMap.begin(), intMap.end());
			intMap.Insert(p1);
			Assert::AreNotEqual(intMap.begin(), intMap.end());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			Assert::AreEqual(charPtrMap.begin(), charPtrMap.end());
			charPtrMap.Insert(char1);
			Assert::AreNotEqual(charPtrMap.begin(), charPtrMap.end());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			Assert::AreEqual(stringMap.begin(), stringMap.end());
			stringMap.Insert(str);
			Assert::AreNotEqual(stringMap.begin(), stringMap.end());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			Assert::AreEqual(fooMap.begin(), fooMap.end());
			fooMap.Insert(foo);
			Assert::AreNotEqual(fooMap.begin(), fooMap.end());
		}

		TEST_METHOD(Iterator_Assignment_Operator)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;
			HashMap<std::int32_t, std::int32_t>::Iterator it;

			it = intMap.Insert(p1);
			Assert::AreEqual(it, intMap.begin());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			HashMap<char*, std::int32_t>::Iterator it2;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			it2 = charPtrMap.Insert(char1);
			Assert::AreEqual(it2, charPtrMap.begin());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			HashMap<std::string, std::int32_t>::Iterator it3;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			it3 = stringMap.Insert(str);
			Assert::AreEqual(it3, stringMap.begin());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			HashMap<Foo, std::int32_t>::Iterator it4;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			it4 = fooMap.Insert(foo);
			Assert::AreEqual(it4, fooMap.begin());
		}

		TEST_METHOD(Iterator_Comparison_Operators)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.Insert(p1);
			HashMap<std::int32_t, std::int32_t>::Iterator it2 = intMap.begin();
			Assert::IsTrue(it == it2);
			Assert::IsFalse(it != it2);
			it2 = intMap.end();
			Assert::IsFalse(it == it2);
			Assert::IsTrue(it != it2);

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			HashMap<char*, std::int32_t>::Iterator it3 = charPtrMap.Insert(char1);
			HashMap<char*, std::int32_t>::Iterator it4 = charPtrMap.begin();
			Assert::IsTrue(it3 == it4);
			Assert::IsFalse(it3 != it4);
			it4 = charPtrMap.end();
			Assert::IsFalse(it3 == it4);
			Assert::IsTrue(it3 != it4);

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war", f = "dog";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2), str3(f, data);

			HashMap<std::string, std::int32_t>::Iterator it5 = stringMap.Insert(str);
			HashMap<std::string, std::int32_t>::Iterator it6 = stringMap.begin();
			Assert::IsTrue(it5 == it6);
			Assert::IsFalse(it5 != it6);
			it6 = stringMap.end();
			Assert::IsFalse(it5 == it6);
			Assert::IsTrue(it5 != it6);

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			HashMap<Foo, std::int32_t>::Iterator it7 = fooMap.Insert(foo);
			HashMap<Foo, std::int32_t>::Iterator it8 = fooMap.begin();
			Assert::IsTrue(it7 == it8);
			Assert::IsFalse(it7 != it8);
			it8 = fooMap.end();
			Assert::IsFalse(it7 == it8);
			Assert::IsTrue(it7 != it8);
		}

		TEST_METHOD(Iterator_PostIncrement_Operator)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.Insert(p1);
			HashMap<std::int32_t, std::int32_t>::Iterator it2 = intMap.Insert(p2);
			HashMap<std::int32_t, std::int32_t>::Iterator it3 = intMap.begin();
			Assert::AreEqual(it3++, it2);
			Assert::AreEqual(it3++, it);
			Assert::AreEqual(it3, intMap.end());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey", *b = "yeh";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2);

			HashMap<char*, std::int32_t>::Iterator it4 = charPtrMap.Insert(char1);
			HashMap<char*, std::int32_t>::Iterator it5 = charPtrMap.Insert(char2);
			HashMap<char*, std::int32_t>::Iterator it6 = charPtrMap.begin();
			Assert::AreEqual(it6++, it4);
			Assert::AreEqual(it6++, it5);
			Assert::AreEqual(it6, charPtrMap.end());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2);

			HashMap<std::string, std::int32_t>::Iterator it7 = stringMap.Insert(str);
			HashMap<std::string, std::int32_t>::Iterator it8 = stringMap.Insert(str2);
			HashMap<std::string, std::int32_t>::Iterator it9 = stringMap.begin();
			Assert::AreEqual(it9++, it7);
			Assert::AreEqual(it9++, it8);
			Assert::AreEqual(it9, stringMap.end());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			HashMap<Foo, std::int32_t>::Iterator it10 = fooMap.Insert(foo);
			HashMap<Foo, std::int32_t>::Iterator it11 = fooMap.Insert(foo2);
			HashMap<Foo, std::int32_t>::Iterator it12 = fooMap.begin();
			Assert::AreEqual(it12++, it11);
			Assert::AreEqual(it12++, it10);
			Assert::AreEqual(it12, fooMap.end());
		}

		TEST_METHOD(Iterator_PreIncrement_Operator)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2), p2(data2, data);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.Insert(p1);
			HashMap<std::int32_t, std::int32_t>::Iterator it2 = intMap.Insert(p2);
			HashMap<std::int32_t, std::int32_t>::Iterator it3 = intMap.begin();
			Assert::AreEqual(it3, it2);
			Assert::AreEqual(++it3, it);
			Assert::AreEqual(++it3, intMap.end());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey", *b = "yeh";
			std::pair<char*, std::int32_t> char1(a, data), char2(b, data2);

			HashMap<char*, std::int32_t>::Iterator it4 = charPtrMap.Insert(char1);
			HashMap<char*, std::int32_t>::Iterator it5 = charPtrMap.Insert(char2);
			HashMap<char*, std::int32_t>::Iterator it6 = charPtrMap.begin();
			Assert::AreEqual(it6, it4);
			Assert::AreEqual(++it6, it5);
			Assert::AreEqual(++it6, charPtrMap.end());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw", e = "war";
			std::pair<std::string, int32_t> str(d, data), str2(e, data2);

			HashMap<std::string, std::int32_t>::Iterator it7 = stringMap.Insert(str);
			HashMap<std::string, std::int32_t>::Iterator it8 = stringMap.Insert(str2);
			HashMap<std::string, std::int32_t>::Iterator it9 = stringMap.begin();
			Assert::AreEqual(it9, it7);
			Assert::AreEqual(++it9, it8);
			Assert::AreEqual(++it9, stringMap.end());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data), h(data2);
			std::pair<Foo, std::int32_t> foo(g, data), foo2(h, data);

			HashMap<Foo, std::int32_t>::Iterator it10 = fooMap.Insert(foo);
			HashMap<Foo, std::int32_t>::Iterator it11 = fooMap.Insert(foo2);
			HashMap<Foo, std::int32_t>::Iterator it12 = fooMap.begin();
			Assert::AreEqual(it12, it11);
			Assert::AreEqual(++it12, it10);
			Assert::AreEqual(++it12, fooMap.end());
		}

		TEST_METHOD(Iterator_Dereference_Operators)
		{
			std::int32_t data = 10, data2 = 20;
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			HashMap<std::int32_t, std::int32_t>::Iterator it = intMap.begin();
			const HashMap<std::int32_t, std::int32_t>::Iterator errorIt(it);
			
			auto intExpression = [&it] {*it; };
			Assert::ExpectException<std::exception>(intExpression);
			auto intExpression2 = [&it] {it->second; };
			Assert::ExpectException<std::exception>(intExpression2);
			auto intExpression3 = [&errorIt] {*errorIt; };
			Assert::ExpectException<std::exception>(intExpression3);
			auto intExpression4 = [&errorIt] {errorIt->second; };
			Assert::ExpectException<std::exception>(intExpression4);

			it = intMap.Insert(p1);
			const HashMap<std::int32_t, std::int32_t>::Iterator constIt(it);
			Assert::IsTrue(p1 == *it);
			Assert::AreEqual(it->second, data2);
			Assert::IsTrue(p1 == *constIt);
			Assert::AreEqual(constIt->second, data2);

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			HashMap<char*, std::int32_t>::Iterator it2 = charPtrMap.begin();
			const HashMap<char*, std::int32_t>::Iterator errorIt2(it2);

			auto charExpression = [&it2] {*it2; };
			Assert::ExpectException<std::exception>(charExpression);
			auto charExpression2 = [&it2] {it2->second; };
			Assert::ExpectException<std::exception>(charExpression2);
			auto charExpression3 = [&errorIt2] {*errorIt2; };
			Assert::ExpectException<std::exception>(charExpression3);
			auto charExpression4 = [&errorIt2] {errorIt2->second; };
			Assert::ExpectException<std::exception>(charExpression4);

			it2 = charPtrMap.Insert(char1);
			const HashMap<char*, std::int32_t>::Iterator constIt2(it2);
			Assert::IsTrue(char1 == *it2);
			Assert::AreEqual(it2->second, data);
			Assert::IsTrue(char1 == *constIt2);
			Assert::AreEqual(constIt2->second, data);

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			HashMap<std::string, std::int32_t>::Iterator it3 = stringMap.begin();
			const HashMap<std::string, std::int32_t>::Iterator errorIt3(it3);

			auto stringExpression = [&it3] {*it3; };
			Assert::ExpectException<std::exception>(stringExpression);
			auto stringExpression2 = [&it3] {it3->second; };
			Assert::ExpectException<std::exception>(stringExpression2);
			auto stringExpression3 = [&errorIt3] {*errorIt3; };
			Assert::ExpectException<std::exception>(stringExpression3);
			auto stringExpression4 = [&errorIt3] {errorIt3->second; };
			Assert::ExpectException<std::exception>(stringExpression4);

			it3 = stringMap.Insert(str);
			const HashMap<std::string, std::int32_t>::Iterator constIt3(it3);
			Assert::IsTrue(str == *it3);
			Assert::AreEqual(it3->second, data);
			Assert::IsTrue(str == *constIt3);
			Assert::AreEqual(constIt3->second, data);

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			HashMap<Foo, std::int32_t>::Iterator it4 = fooMap.begin();
			const HashMap<Foo, std::int32_t>::Iterator errorIt4(it4);

			auto fooExpression = [&it4] {*it4; };
			Assert::ExpectException<std::exception>(fooExpression);
			auto fooExpression2 = [&it4] {it4->second; };
			Assert::ExpectException<std::exception>(fooExpression2);
			auto fooExpression3 = [&errorIt4] {*errorIt4; };
			Assert::ExpectException<std::exception>(fooExpression3);
			auto fooExpression4 = [&errorIt4] {errorIt4->second; };
			Assert::ExpectException<std::exception>(fooExpression4);

			it4 = fooMap.Insert(foo);
			const HashMap<Foo, std::int32_t>::Iterator constIt4(it4);
			Assert::IsTrue(foo == *it4);
			Assert::AreEqual(it4->second, data);
			Assert::IsTrue(foo == *constIt4);
			Assert::AreEqual(constIt4->second, data);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}