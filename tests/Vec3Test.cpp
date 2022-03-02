#include "stdafx.h"
#include "CppUnitTest.h"
#include "reMath/reVec3d.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace re;

namespace Test
{
	TEST_CLASS(Vec3UnitTest)
	{
	public:
		TEST_METHOD(BasicVec3Test)
		{
			// Length (magnitude).
			Vec3d v1(2.f, 3.f, 4.f);
			Assert::AreEqual(5.3851648071345040312507104915403f, v1.length(), L"Vector magnitutde incorrect", LINE_INFO());

			// Parallel check.
			Vec3d v2(3.f, 4.5f, 0.1f);
			Assert::IsFalse(v1.isParallel(v2), L"Vector parallel check failed", LINE_INFO());

			const Vec3d v3(4.f, 6.f, 8.f);
			Assert::IsTrue(v1.isParallel(v3), L"Vector parallel check failed", LINE_INFO());

			// Distance calculation.
			Assert::AreEqual(4.29651f, v1.distanceTo(v2), L"Distance calculation failed", LINE_INFO());
			Assert::AreNotEqual(4.29651f, v1.distanceTo(v3), L"Distance calculation failed", LINE_INFO());

			// Normalize.
			v1.normalize();
			Assert::AreEqual(0.3713906763541037262931524476924f, v1.x, L"Vector normalization failed", LINE_INFO());
			Assert::AreEqual(0.742781352708207452586304895385f, v1.z, L"Vector normalization failed", LINE_INFO());

			// Negate.
			v1.negate();
			Assert::AreEqual(-0.37139067635410372629315244769244f, v1.x, L"Vector negation failed", LINE_INFO());
			Assert::AreEqual(-0.74278135270820745258630489538488f, v1.z, L"Vector negation failed", LINE_INFO());

			// Cross product.
			v2.set(3.f, 2.f, 1.f);
			//Assert::AreEqual(Vec3d(), v1.cross(v2), L"Vector cross product calculation failed");

			// Dot product.
			//Assert::AreEqual(-5.4083269131959839396788319012058f, v1.dot(v2), L"Vector dot product calculation failed");

			// Distance to another vector.
			//v1.set(1.f, 1.f);
			//Assert::AreEqual(4.0311288741492748261833066151519f, v1.distanceTo(v2), L"Distance to vector failed");
			//Assert::AreEqual(8.6023252670426267717294735350497f, v1.distanceTo(v3), L"Distance to vector failed");
		}

		TEST_METHOD(OperatorsVec3Test)
		{
			
		}
	};
}
