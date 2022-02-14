#include "stdafx.h"
#include "CppUnitTest.h"
#include "reMathUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace re;

namespace Test
{
	TEST_CLASS(UtilsUnitTest)
	{
	public:
		TEST_METHOD(BasicUtilsUnitTest)
		{
			// Radiand/degrees conversion.
			Assert::AreEqual(PI, toRadians(180), L"To radians conversion failed.");
			Assert::AreEqual(180.f, toDegrees(PI), L"To degrees conversion failed.");

			// Max power of 2.
			Assert::AreEqual(static_cast<unsigned long>(8), maxPowerOfTwo(257), L"Max power of 2 failed.");
			Assert::AreEqual(static_cast<unsigned long>(8), maxPowerOfTwo(256), L"Max power of 2 failed.");
			Assert::AreEqual(static_cast<unsigned long>(7), maxPowerOfTwo(200), L"Max power of 2 failed.");
			Assert::AreEqual(static_cast<unsigned long>(5), maxPowerOfTwo(37), L"Max power of 2 failed.");
			Assert::AreEqual(static_cast<unsigned long>(1), maxPowerOfTwo(2), L"Max power of 2 failed.");
			Assert::AreEqual(static_cast<unsigned long>(0), maxPowerOfTwo(1), L"Max power of 2 failed.");
			Assert::AreEqual(static_cast<unsigned long>(0), maxPowerOfTwo(0), L"Max power of 2 failed.");
		}
	};
}
