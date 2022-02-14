#include "stdafx.h"
#include "CppUnitTest.h"
#include "reVec2d.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace re;

namespace Test
{		
	TEST_CLASS(Vec2UnitTest)
	{
	public:
		TEST_METHOD(BasicVec2Test)
		{
			// Length (magnitude).
			Vec2d v1(2.f, 3.f);
			Assert::AreEqual(3.6055512754639892931192212674705f, v1.length(), L"Vector magnitutde incorrect");

			// Parallel check.
			const Vec2d v2(3.f, 4.5f);
			Assert::IsTrue(v1.isParallel(v2), L"Vector parallel check failed");

			const Vec2d v3(-4.f, -6.f);
			Assert::IsTrue(v1.isParallel(v3), L"Vector parallel check failed");
			
			// Normalize.
			v1.normalize();
			Assert::AreEqual(0.554700196225229122018341733457f, v1.x, L"Vector normalization failed");
			Assert::AreEqual(0.8320502943378436830275126001855f, v1.y, L"Vector normalization failed");

			// Negate.
			v1.negate();
			Assert::AreEqual(-0.554700196225229122018341733457f, v1.x, L"Vector negation failed");
			Assert::AreEqual(-0.8320502943378436830275126001855f, v1.y, L"Vector negation failed");

			// Cross product.
			Assert::AreEqual(0.f, v1.cross(v2), L"Vector cross product calculation failed");

			// Dot product.
			Assert::AreEqual(-5.4083269131959839396788319012058f, v1.dot(v2), L"Vector dot product calculation failed");

			// Distance to another vector.
			v1.set(1.f, 1.f);
			Assert::AreEqual(4.0311288741492748261833066151519f, v1.distanceTo(v2), L"Distance to vector failed");
			Assert::AreEqual(8.6023252670426267717294735350497f, v1.distanceTo(v3), L"Distance to vector failed");
		}

		TEST_METHOD(OperatorsVec2Test)
		{
			// Comparison operators.
			Vec2d v1(2.f, 3.f);
			const Vec2d v2(2.f, 3.f);
			const Vec2d v3(-1.f, 3.f);
			Assert::IsTrue(v1 == v2, L"Vector comparison failed");
			Assert::IsFalse(v1 == v3, L"Vector comparison failed");

			// Assignment operators.
			const Vec2d assign = v2;
			Assert::IsTrue(assign == v2, L"Assignment failed");
			Assert::IsFalse(assign == v3, L"Assignment failed");

			// Arithmetic operators.
			const Vec2d negate(-v2);
			Assert::IsTrue(-negate == v2, L"Unary minus failed");
			Assert::IsTrue(negate != v2, L"Unary minus failed");
			Assert::IsTrue(v2 + v3 == Vec2d(1, 6), L"Vector addition failed");
			Assert::IsTrue(v2 - v3 == Vec2d(3, 0), L"Vector substraction failed");
			Assert::IsTrue(v3 * 2.f == Vec2d(-2, 6), L"Vector multiplication by float failed");
			Assert::IsTrue(2.f * v3 == Vec2d(-2, 6), L"Vector multiplication by float failed");

			// Compound assignment operators.
			Vec2d compound(v2);
			compound += v3;
			Assert::IsTrue(compound == Vec2d(1, 6), L"Vector compound addition failed");
			compound -= v2;
			Assert::IsTrue(compound == v3, L"Vector compound substraction failed");
			compound += 1.f;
			Assert::IsTrue(compound == Vec2d(0, 4), L"Vector compound float addition failed");
			compound -= 3.f;
			Assert::IsTrue(compound == Vec2d(-3, 1), L"Vector compound float substraction failed");
			compound *= 3.f;
			Assert::IsTrue(compound == Vec2d(-9, 3), L"Vector compound float multiplication failed");
			compound /= 2.f;
			Assert::IsTrue(compound == Vec2d(-4.5f, 1.5f), L"Vector compound float division failed");

			// Conversion operators.
			float* access1(v1);
			Assert::AreEqual(2.f, access1[0], L"Non-const access failed"/*, LINE_INFO()*/); // LINE_INFO will show the breaking line when there's no PDB present.
			Assert::AreEqual(3.f, access1[1], L"Non-const access failed");

			access1[1] += 2.f;
			Assert::AreEqual(5.f, v1.y, L"Non-const modification failed");

			const float* access2(v1);
			Assert::AreEqual(2.f, access1[0], L"Const access failed");
			Assert::AreEqual(5.f, access1[1], L"Const access failed");

			// Subscript operators.
			Assert::IsTrue(v2[1] == 3.f, L"Array access failed");
			Vec2d access3(v2);
			access3[1] = 31.f;
			Assert::IsTrue(access3.y == 31.f, L"Array access failed");
		}
	};
}
