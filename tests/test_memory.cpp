#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "include/Merlot/types.hpp"
#include "include/Merlot/memory.hpp"

using ::testing::ElementsAre;

TEST(MemoryManagementTest, MemoryAllocationTest) {
    ml::Memory::reserve(1024*1024*1024, "test");

    void* ptr_1 = ml::Memory::allocate(10, ml::type::float32, "test");
    void* ptr_2 = ml::Memory::allocate(10, ml::type::int32, "test");

    for(int i = 0; i < 10; i++) {
        static_cast<float*>(ptr_1)[i] = 1.0f;
        static_cast<int*>(ptr_2)[i] = 1;
    }

    for(int i = 0; i < 10; i++) {
        ASSERT_EQ(static_cast<float*>(ptr_1)[i], 1.0f);
        ASSERT_EQ(static_cast<int*>(ptr_2)[i], 1);
    }
}