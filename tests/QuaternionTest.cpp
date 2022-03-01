#include "stdafx.h"
#include "CppUnitTest.h"
#include "reMath/reQuaternion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace re;

namespace Test
{
	TEST_CLASS(QuaternionUnitTest)
	{
	public:
		TEST_METHOD(BasicQuaternionTest)
		{
			Quaternion q1(2.f, 3.f, 4.f, 5.f);
			Assert::AreEqual(7.3484692283495342945918522241177f, q1.length(), L"Quaternion magnitutde incorrect");

			//const re::Vec3d v2(3.f, 4.5f);
			//Assert::IsTrue(v1.isParallel(v2), L"Vector parallel check failed"/*, LINE_INFO()*/);

			// TODO: ...
		}
	};
}
