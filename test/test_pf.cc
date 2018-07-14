#include "pf.h"
#include <gtest/gtest.h>

TEST(TestPF, CreateFile) {
  PF_Manager pf;
  const char *file = "hello.txt";

  ASSERT_EQ(PF_OK, pf.CreateFile(file));
  ASSERT_EQ(PF_ERROR, pf.CreateFile(file));
  unlink(file);
}

TEST(TestPF, DestroyFile) {
  PF_Manager pf;
  const char *file = "hello.txt";

  ASSERT_EQ(PF_ERROR, pf.DestroyFile(file));
  ASSERT_EQ(PF_OK, pf.CreateFile(file));
  ASSERT_EQ(PF_OK, pf.DestroyFile(file));
  ASSERT_EQ(PF_ERROR, pf.DestroyFile(file));
}

TEST(TestPF, OpenFile) {
  PF_Manager pf;
  PF_FileHandle handle;
  const char *file = "hello.txt";

  ASSERT_EQ(PF_ERROR, pf.OpenFile(file, handle));
  ASSERT_EQ(PF_OK, pf.CreateFile(file));
  ASSERT_EQ(PF_OK, pf.OpenFile(file, handle));
  ASSERT_EQ(PF_OK, pf.CloseFile(handle));
  ASSERT_EQ(PF_OK, pf.DestroyFile(file));
}

TEST(TestPF, CloseFile) {
  PF_Manager pf;
  PF_FileHandle handle;
  const char *file = "hello.txt";

  ASSERT_EQ(PF_ERROR, pf.CloseFile(handle));
  ASSERT_EQ(PF_OK, pf.CreateFile(file));
  ASSERT_EQ(PF_OK, pf.OpenFile(file, handle));
  ASSERT_EQ(PF_OK, pf.CloseFile(handle));
  ASSERT_EQ(PF_OK, pf.DestroyFile(file));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

