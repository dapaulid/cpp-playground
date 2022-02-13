#include <gtest/gtest.h>

#include <queue>
#include <functional>

#include "command.h"
#include "utils/copy_tracker.h"

TEST(Command, Assign) {
  CopyTracker t1, t2;

  //std::function<void(void)> cmd;
  Command cmd = [t1](){};
  cmd = [t2](){};
  cmd = nullptr;
  
  EXPECT_EQ(1, t1.get_copy_count());
  EXPECT_EQ(1, t1.get_move_count());
  EXPECT_EQ(2, t1.get_destroy_count());

  EXPECT_EQ(1, t2.get_copy_count());
  EXPECT_EQ(1, t2.get_move_count());
  EXPECT_EQ(2, t2.get_destroy_count());  

  //std::function f = [t](){};
}

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
  EXPECT_EQ(1, tracker.get_copy_count());
  EXPECT_EQ(1, tracker.get_move_count());
}

TEST(Command, ExecLambda2) {

  int foo = 1;
  CopyTracker tracker;
  std::function cmd([&foo, tracker](){
    foo++;
  });

  EXPECT_EQ(1, foo);
  cmd();
  EXPECT_EQ(2, foo);
  // non-functional: number of copies performed
  EXPECT_EQ(1, tracker.get_copy_count());
}

TEST(Command, ExecFromQueue) {
  int foo = 1;

  std::queue<Command<>> q;
  q.emplace([&foo](){
    foo++;
  });

  EXPECT_EQ(1, foo);
  q.front().execute();
  q.pop();
  EXPECT_EQ(2, foo);
}