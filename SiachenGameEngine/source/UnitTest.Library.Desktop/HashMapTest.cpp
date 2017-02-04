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
			std::pair<std::int32_t, int32_t> p1(data, data2);

			// Testing for an integer
			HashMap<std::int32_t, std::int32_t> intMap;

			intMap.Insert(p1);
			Assert::IsTrue(intMap.ContainsKey(data));
			Assert::AreEqual(1U, intMap.Size());
			intMap.Clear();
			Assert::AreEqual(0U, intMap.Size());

			// Testing for character pointer
			HashMap<char*, std::int32_t> charPtrMap;
			char* a = "hey";
			std::pair<char*, std::int32_t> char1(a, data);

			charPtrMap.Insert(char1);
			Assert::IsTrue(charPtrMap.ContainsKey(a));
			Assert::AreEqual(1U, charPtrMap.Size());
			charPtrMap.Clear();
			Assert::AreEqual(0U, charPtrMap.Size());

			//Testing for string
			HashMap<std::string, std::int32_t> stringMap;
			std::string d = "raw";
			std::pair<std::string, int32_t> str(d, data);

			stringMap.Insert(str);
			Assert::IsTrue(stringMap.ContainsKey(d));
			Assert::AreEqual(1U, stringMap.Size());
			stringMap.Clear();
			Assert::AreEqual(0U, stringMap.Size());

			//Testing for Foos
			HashMap<Foo, std::int32_t> fooMap;
			Foo g(data);
			std::pair<Foo, std::int32_t> foo(g, data);

			fooMap.Insert(foo);
			Assert::IsTrue(fooMap.ContainsKey(g));
			Assert::AreEqual(1U, fooMap.Size());
			fooMap.Clear();
			Assert::AreEqual(0U, fooMap.Size());
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

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}