#include "Observer.h"
#include "TimedBlock.h"

#include <fstream>
#include <iostream>
#include <sstream>

void CoutObserver::update(std::shared_ptr<TimedBlock> timedBlock)
{
  std::cout << *timedBlock;
}

void LogObserver::update(std::shared_ptr<TimedBlock> timedBlock)
{
  std::ofstream ofile(getFileName(timedBlock->d_timeStamp));

  ofile << *timedBlock;

  ofile.close();
}

std::string LogObserver::getFileName(const std::time_t &time) const
{
  std::ostringstream oss;
  oss << "bulk" << time << ".log";
  return oss.str();
}
