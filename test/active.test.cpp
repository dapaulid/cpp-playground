#include <gtest/gtest.h>

#include "active.h"
#include "utils/copy_tracker.h"

class MyActiveObject: public ActiveObject {
 protected:
  int i_foo(int x, CopyTracker) {
    return x+1;
  }

 public:
  template<typename C>
  void foo(int x, CopyTracker t, C&& cb) {
    // TODO without lambda?
    //dispatch(std::mem_fn(&MyActiveObject::i_foo), cb, x, t);
    dispatch([=](){
      return i_foo(x, t);
    }, cb);//, x, t);
  }



};

int foo(int x, CopyTracker) {
  return x+1;
}

TEST(ActiveObject, dispatch) {
  
  ActiveObject a;
  CopyTracker t1, t2;

  int result = 0;
  a.dispatch(foo, [&result, t1](int ret){
    result = ret;
  }, 122, t2);

  EXPECT_EQ(0, result);

  EXPECT_EQ(1, t1.get_copy_count());
  EXPECT_EQ(2, t1.get_move_count());
  EXPECT_EQ(2, t1.get_destroy_count());
  
  EXPECT_EQ(1, t2.get_copy_count());
  EXPECT_EQ(1, t2.get_move_count());
  EXPECT_EQ(1, t2.get_destroy_count());  

  a.process();

  EXPECT_EQ(123, result);
  
  EXPECT_EQ(1, t1.get_copy_count());
  EXPECT_EQ(2, t1.get_move_count());
  EXPECT_EQ(3, t1.get_destroy_count());
  
  EXPECT_EQ(2, t2.get_copy_count()); // can we do better?
  EXPECT_EQ(1, t2.get_move_count());
  EXPECT_EQ(3, t2.get_destroy_count());  

}

TEST(ActiveObject, subclass_dispatch) {
  
  MyActiveObject a;
  CopyTracker t1, t2;

  int result = 0;
  a.foo(122, t2, [&result, t1](int ret){
    result = ret;
  });

  EXPECT_EQ(0, result);

  EXPECT_EQ(1, t1.get_copy_count());
  EXPECT_EQ(2, t1.get_move_count());
  EXPECT_EQ(2, t1.get_destroy_count());
  
  EXPECT_EQ(1, t2.get_copy_count());
  EXPECT_EQ(1, t2.get_move_count());
  EXPECT_EQ(1, t2.get_destroy_count());  

  a.process();

  EXPECT_EQ(123, result);
  
  EXPECT_EQ(1, t1.get_copy_count());
  EXPECT_EQ(2, t1.get_move_count());
  EXPECT_EQ(3, t1.get_destroy_count());
  
  EXPECT_EQ(2, t2.get_copy_count()); // can we do better?
  EXPECT_EQ(1, t2.get_move_count());
  EXPECT_EQ(3, t2.get_destroy_count());  

}