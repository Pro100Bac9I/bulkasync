#include "HandlersCollection.h"
#include "bulk/LineProcessor.h"

#include <mutex>


HandlerCollection& HandlerCollection::getInstance() 
{
  static HandlerCollection instance;
  return instance;
}

handle_t HandlerCollection::connect(size_t i_bulk)
{
  std::lock_guard<std::mutex> lk(d_mutex);
  d_handlers[++d_counter] = std::make_unique<LineProcessor>(i_bulk);
  return reinterpret_cast<void *>(d_counter);
}

void HandlerCollection::receive(handle_t i_handle, const char *i_data, std::size_t i_size)
{
  std::lock_guard<std::mutex> lk(d_mutex);
  d_handlers[reinterpret_cast<long>(i_handle)]->processLine(i_data, i_size);
}

void HandlerCollection::disconnect(handle_t i_handle)
{
  std::lock_guard<std::mutex> lk(d_mutex);
  auto it = d_handlers.find(reinterpret_cast<long>(i_handle));
  if (it != d_handlers.end())
    d_handlers.erase(it);
}
