#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < 4; i++) {
		v[i] = i;
	}
	TDynamicVector<int> cpy(v);

	ASSERT_EQ(v.size(), cpy.size());
	EXPECT_EQ(v, cpy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < 4; i++) {
		v[i] = i;
	}
	TDynamicVector<int> cpy(v);

	v[0] = 100;
	EXPECT_NE(cpy[0], 100);
  
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(6) = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v.size(), 4);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
	EXPECT_EQ(v[3], 4);

}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> v1(4);
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v1.size(), 4);
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);
	EXPECT_EQ(v1[2], 3);
	EXPECT_EQ(v1[3], 4);

	EXPECT_EQ(v.size(), 4);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
	EXPECT_EQ(v[3], 4);
	
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> v1(5);
	
	ASSERT_NE(v.size(), v1.size());
	v1 = v;
	EXPECT_EQ(v.size(), v1.size());
	EXPECT_EQ(v1.size(), 4u);

}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> v1(5);
	v1 = v;
	ASSERT_EQ(v1.size(), 4u);
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);
	EXPECT_EQ(v1[2], 3);
	EXPECT_EQ(v1[3], 4);
	v[0] = 100;
	EXPECT_EQ(v1[0], 1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	for (int i = 0; i < 4; i++) {
		v[i] = i + 1;
		v1[i] = i + 1;
	}
	EXPECT_TRUE(v == v1);
	EXPECT_FALSE(v != v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	EXPECT_TRUE(v == v);
	EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(5);
	EXPECT_FALSE(v == v1);
	EXPECT_TRUE(v != v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> res = v + 10;
	ASSERT_EQ(res.size(), 4u);
	EXPECT_EQ(res[0], 11);
	EXPECT_EQ(res[1], 12);
	EXPECT_EQ(res[2], 13);
	EXPECT_EQ(res[3], 14);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> res = v - 1;
	ASSERT_EQ(res.size(), 4u);
	EXPECT_EQ(res[0], 0);
	EXPECT_EQ(res[1], 1);
	EXPECT_EQ(res[2], 2);
	EXPECT_EQ(res[3], 3);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> res = v*2;
	ASSERT_EQ(res.size(), 4u);
	EXPECT_EQ(res[0], 2);
	EXPECT_EQ(res[1], 4);
	EXPECT_EQ(res[2], 6);
	EXPECT_EQ(res[3], 8);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> v1(4);
	v1[0] = 2; v1[1] = 2; v1[2] = 2; v1[3] = 2;
	TDynamicVector<int> res = v + v1;
	ASSERT_EQ(res.size(), 4u);
	EXPECT_EQ(res[0], 3);
	EXPECT_EQ(res[1], 4);
	EXPECT_EQ(res[2], 5);
	EXPECT_EQ(res[3], 6);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(TDynamicVector<int> res = v1 + v);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> v1(4);
	v1[0] = 2; v1[1] = 2; v1[2] = 2; v1[3] = 2;
	TDynamicVector<int> res = v - v1;
	ASSERT_EQ(res.size(), 4u);
	EXPECT_EQ(res[0], -1);
	EXPECT_EQ(res[1], 0);
	EXPECT_EQ(res[2], 1);
	EXPECT_EQ(res[3], 2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(TDynamicVector<int> res = v1 - v);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;
	TDynamicVector<int> v1(4);
	v1[0] = 2; v1[1] = 2; v1[2] = 2; v1[3] = 2;
	int res = v * v1;
	EXPECT_EQ(res, 20);
	
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(5);
	//ASSERT_DEATH(v * v1, "");
	ASSERT_ANY_THROW(v * v1);
}

