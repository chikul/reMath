#include "stdafx.h"
#include "CppUnitTest.h"
#include "reMath/reMatrix3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace re;

namespace Test
{
	TEST_CLASS(Matrix3UnitTest)
	{
	public:
		TEST_METHOD(BasicMatrix3Test)
		{
			//Vec3d v1(2.f, 3.f, 4.f);
			//Assert::AreEqual(5.3851648071345040312507104915403f, v1.length(), L"Vector magnitutde incorrect"/*, LINE_INFO()*/);

			//const re::Vec3d v2(3.f, 4.5f);
			//Assert::IsTrue(v1.isParallel(v2), L"Vector parallel check failed"/*, LINE_INFO()*/);

			// TODO: ...
		}

		TEST_METHOD(OperatorsMatrix3Test)
		{
			/*re::Vec2d v1(2.f, 3.f);
			float* access1(v1);
			Assert::AreEqual(2.f, access1[0], L"Non-const access failed");
			Assert::AreEqual(3.f, access1[1], L"Non-const access failed");

			access1[1] += 2.f;
			Assert::AreEqual(5.f, v1.y, L"Non-const modification failed");

			const float* access2(v1);
			Assert::AreEqual(2.f, access1[0], L"Const access failed"/);
			Assert::AreEqual(5.f, access1[1], L"Const access failed");*/
		}
	};
}
