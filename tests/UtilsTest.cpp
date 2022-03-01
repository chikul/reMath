#include "stdafx.h"
#include "CppUnitTest.h"
#include "reMath/reMathUtil.h"
#include "reMath/reMatrix4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace re;

namespace Test
{
	TEST_CLASS(UtilsUnitTest)
	{
	public:
		TEST_METHOD(BasicUtilsUnitTest)
		{
			// Radians/degrees conversion.
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

			// Get high nibble.
			Assert::AreEqual(static_cast <unsigned char>(0), getHighNibble(1), L"Get high nibble failed.");
			Assert::AreEqual(static_cast <unsigned char>(32), getHighNibble(42), L"Get high nibble failed.");
			Assert::AreEqual(static_cast <unsigned char>(112), getHighNibble(127), L"Get high nibble failed.");

			// Get low nibble.
			Assert::AreEqual(static_cast <unsigned char>(1), getLowNibble(1), L"Get low nibble failed.");
			Assert::AreEqual(static_cast <unsigned char>(10), getLowNibble(42), L"Get low nibble failed.");
			Assert::AreEqual(static_cast <unsigned char>(15), getLowNibble(127), L"Get low nibble failed.");

			// Perspective matrix.
			auto matrix = perspective(45.f, 640.f / 480.f);
		}
	};
}
