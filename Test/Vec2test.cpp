#include "stdafx.h"
#include "CppUnitTest.h"
#include "reVec2d.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{		
	TEST_CLASS(Vec2UnitTest)
	{
	public:
		TEST_METHOD(BasicVec2Test)
		{
			// Length (magnitude)
			re::Vec2d v1(2.f, 3.f);
			Assert::AreEqual(3.6055512754639892931192212674705f, v1.length(), L"Vector magnitutde incorrect");

			// Parallel check
			const re::Vec2d v2(3.f, 4.5f);
			Assert::IsTrue(v1.isParallel(v2), L"Vector parallel check failed");

			const re::Vec2d v3(-4.f, -6.f);
			Assert::IsTrue(v1.isParallel(v3), L"Vector parallel check failed");
			
			// Normalize
			v1.normalize();
			Assert::AreEqual(0.554700196225229122018341733457f, v1.x, L"Vector normalization failed");
			Assert::AreEqual(0.8320502943378436830275126001855f, v1.y, L"Vector normalization failed");

			// Negate
			v1.negate();
			Assert::AreEqual(-0.554700196225229122018341733457f, v1.x, L"Vector negation failed");
			Assert::AreEqual(-0.8320502943378436830275126001855f, v1.y, L"Vector negation failed");

			// Cross product
			Assert::AreEqual(0.f, v1.cross(v2), L"Vector cross product calculation failed");

			// Dot product
			Assert::AreEqual(-5.4083269131959839396788319012058f, v1.dot(v2), L"Vector dot product calculation failed");
		}

		TEST_METHOD(OperatorsVec2Test)
		{
			// Comparison operators
			re::Vec2d v1(2.f, 3.f);
			const re::Vec2d v2(2.f, 3.f);
			const re::Vec2d v3(-1.f, 3.f);
			Assert::IsTrue(v1 == v2, L"Vector comparison failed");
			Assert::IsFalse(v1 == v3, L"Vector comparison failed");

			// TODO: ...

			// Conversion operators
			float* access1(v1);
			Assert::AreEqual(2.f, access1[0], L"Non-const access failed"/*, LINE_INFO()*/); // LINE_INFO will show the breaking line when there's no PDB present.
			Assert::AreEqual(3.f, access1[1], L"Non-const access failed");

			access1[1] += 2.f;
			Assert::AreEqual(5.f, v1.y, L"Non-const modification failed");

			const float* access2(v1);
			Assert::AreEqual(2.f, access1[0], L"Const access failed");
			Assert::AreEqual(5.f, access1[1], L"Const access failed");
		}
	};
}
