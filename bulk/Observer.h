#pragma once

#include <memory>
#include <string>
#include <ctime>

struct TimedBlock;

class Observer
{
public:
  Observer() = default;
  virtual ~Observer() = default;

  virtual void update(std::shared_ptr<TimedBlock> commands) = 0;
};

class CoutObserver : public Observer
{
public:
  CoutObserver() = default;

  void update(std::shared_ptr<TimedBlock> timedBlock) override;
};

class LogObserver : public Observer
{
public:
  LogObserver() = default;

  void update(std::shared_ptr<TimedBlock> timedBlock) override;

  std::string getFileName(const std::time_t &time) const;
};
