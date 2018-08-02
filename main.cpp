#include "async.h"

#include <thread>
#include <iostream>
#include <chrono>

void oneThreadManyContextsTest(int val1, int val2)
{
  auto h = async::connect(val1);
  auto h2 = async::connect(val2);

  async::receive(h, "aaa\nbbb\nccc\n", 12);
  async::receive(h2, "aaa\nbbb\nccc\n", 12);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  async::receive(h, "aaa\nbbb\n{\nccc", 13);
  async::receive(h2, "aaa\nbbb\n{\nccc", 13);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  async::receive(h2, "aaa\nbbb\nccc\n}", 13);
  async::receive(h, "aaa\nbbb\nccc\n}", 13);
  async::receive(h, "aaa\n}\nbbb\nccc", 13);
  async::receive(h2, "aaa\n}\nbbb\nccc", 13);
  async::receive(h, "aaa\nbbb\nccc\n", 12);
  async::receive(h2, "aaa\nbbb\n{\nccc", 13);
  async::receive(h, "aaa\nbbb\nccc\n}", 13);
  async::receive(h2, "aaa\n}\nbbb\nccc", 13);
  
  async::disconnect(h);
  async::disconnect(h2);
}


void twoThreadsTest()
{
  
  auto t = std::thread(oneThreadManyContextsTest, 1, 2);
  auto t2 = std::thread(oneThreadManyContextsTest, 2, 3);

  t.join();
  t2.join();
  
}

int main(int argc, char **argv)
{
  std::cout << "oneThreadManyContextsTest" << std::endl;
  oneThreadManyContextsTest(2, 3);
  std::cout << "\noneThreadManyContextsTest" << std::endl;
  twoThreadsTest();

  return 0;
}
