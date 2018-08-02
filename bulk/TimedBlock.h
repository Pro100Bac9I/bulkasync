#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

using Commands = std::vector<std::string>;

struct TimedBlock
{
  Commands d_commands;
  std::time_t d_timeStamp;

  void clear();

  bool empty() const;

  friend std::ostream& operator<<(std::ostream& os, const TimedBlock &i_block);
};

