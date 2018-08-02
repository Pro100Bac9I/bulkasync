#include "CommandBlock.h"
#include "Observer.h"
#include "TimedBlock.h"

CommandBlock::CommandBlock(int i_len)
  : d_timedBlock(std::make_shared<TimedBlock>())
  , d_status(Status::startBlock)
  , d_blockLen(i_len)
{}


void CommandBlock::setStatus(Status i_status)
{
  if (i_status == Status::endBlock)
  {
    notify();
    d_status = Status::startBlock;
  }

  if (i_status == Status::openBracket)
  {
    notify();
    d_status = Status::openBracket;
  }

  if (i_status == Status::closeBracket)
  {
    notify();
    d_status = Status::startBlock;
  }
}

void CommandBlock::subscribe(std::unique_ptr<Observer> observer)
{
  d_subscribers.push_back(std::move(observer));
}

void CommandBlock::notify()
{
  if (d_timedBlock->empty())
    return;

  for (auto& sub : d_subscribers)
    sub->update(d_timedBlock);

  d_timedBlock->clear();
}

void CommandBlock::append(const std::string & command)
{
  if (d_timedBlock->d_commands.size() == 0)
    d_timedBlock->d_timeStamp = std::time(nullptr);

  if (d_status == Status::startBlock)
  {
    d_timedBlock->d_commands.push_back(command);
    if (d_timedBlock->d_commands.size() == d_blockLen)
      setStatus(Status::endBlock);
  }
  else
    d_timedBlock->d_commands.push_back(command);
}

