#include "async.h"
#include "HandlersCollection.h"

namespace async 
{
  handle_t connect(std::size_t bulk) 
  {
    return HandlerCollection::getInstance().connect(bulk);
  }

  void receive(handle_t handle, const char *data, std::size_t size) 
  {
    HandlerCollection::getInstance().receive(handle, data, size);
  }

  void disconnect(handle_t handle) 
  {
    HandlerCollection::getInstance().disconnect(handle);
  }
}
