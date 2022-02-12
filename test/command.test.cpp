#include <gtest/gtest.h>

#include <queue>

#include "command.h"
#include "utils/copy_tracker.h"


TEST(Command, ExecLambda) {
  int foo = 1;
  CopyTracker tracker;
  Command cmd([&foo, tracker](){
    foo++;
  });

  EXPECT_EQ(1, foo);
  cmd.execute();
  EXPECT_EQ(2, foo);
  // non-functional: number of copies performed
  // TODO: unclear why 2
  EXPECT_EQ(2, tracker.get_copy_count());
}
TEST(Command, ExecFromQueue) {
  int foo = 1;

  std::queue<Command> q;
  q.emplace([&foo](){
    foo++;
  });

  EXPECT_EQ(1, foo);
  q.front().execute();
  q.pop();
  EXPECT_EQ(2, foo);
}