#include <gtest/gtest.h>

#include "../../../src/socs/opencl/Aligned_array.h"

using namespace std;
using namespace socs::opencl;

TEST(aligned_array_test, is_aligned) {
	auto a = make_unique<Aligned_array<uint8_t>>(0);
	ASSERT_TRUE(reinterpret_cast<uintptr_t>(a->array) % Aligned_array<uint8_t>::alignment == 0);
}

TEST(aligned_array_test, create_0_entries) {
	auto a = make_unique<Aligned_array<uint8_t>>(0);
}

TEST(aligned_array_test, create_1_entry) {
	auto a = make_unique<Aligned_array<uint8_t>>(1);
}

TEST(aligned_array_test, create_10_entries) {
	auto a = make_unique<Aligned_array<uint8_t>>(10);
}

TEST(aligned_array_test, length_is_set) {
	auto a = make_unique<Aligned_array<uint8_t>>(10);
	ASSERT_EQ(a->length, 10);
}

TEST(aligned_array_test, values_are_set) {
	auto a = make_unique<Aligned_array<uint8_t>>(2);
	a->array[0] = 123;
	a->array[1] = 45;
	ASSERT_EQ(a->array[0], 123);
	ASSERT_EQ(a->array[1], 45);
}

