#include "TimedBlock.h"


void TimedBlock::clear()
{
  d_commands.clear();
  d_timeStamp = 0;
}

bool TimedBlock::empty() const
{
  return d_commands.empty();
}

std::ostream& operator<<(std::ostream& os, const TimedBlock &i_block)
{
  auto &commands = i_block.d_commands;

  for (auto &command : commands)
    os << command << ' ';

  os << std::endl;

  return os;
}
