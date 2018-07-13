#include "pf.h"
#include <gtest/gtest.h>

TEST(TestPF, CreateFile) {
  PF_Manager pf;
  ASSERT_EQ(PF_OK, pf.CreateFile("hello.txt"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

