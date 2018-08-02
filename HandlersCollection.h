#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>

using handle_t = void*;

class LineProcessor;

class HandlerCollection
{
public:
  static HandlerCollection& getInstance();
  
  handle_t connect(size_t bulk);
  void receive(handle_t handle, const char *data, std::size_t size);
  void disconnect(handle_t handle);

protected:
  HandlerCollection() = default;
  
  HandlerCollection(const HandlerCollection &i_other) = delete;
  HandlerCollection& operator=(const HandlerCollection &i_other) = delete;
private:
  std::unordered_map<int, std::unique_ptr<LineProcessor>> d_handlers;
  std::mutex d_mutex;
  int d_counter = 0;
};
