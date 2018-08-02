#include "LineProcessor.h"
#include "CommandBlock.h"

#include "Observer.h"

#include <string>
#include <iostream>

LineProcessor::LineProcessor(int i_len)
  :d_block(std::make_shared<CommandBlock>(i_len))
{
  d_block->subscribe(std::make_unique<CoutObserver>());
  d_block->subscribe(std::make_unique<LogObserver>());
}

LineProcessor::~LineProcessor()
{
  if (d_tail.size())
    processLine(d_tail);

  d_block->setStatus(Status::endBlock);
}

void LineProcessor::run()
{
  std::string line;

  while (std::getline(std::cin, line))
    processLine(line);
}

void LineProcessor::processLine(const std::string &line)
{
  if (line == "{")
  {
    ++d_bracketCounter;
    if (d_bracketCounter == 1)
      d_block->setStatus(Status::openBracket);
  }
  else if (line == "}")
  {
    --d_bracketCounter;
    if (d_bracketCounter == 0)
      d_block->setStatus(Status::closeBracket);
  }
  else
    d_block->append(line);
}

void LineProcessor::processLine(const char* i_data, size_t i_size)
{
  for (size_t index = 0; index < i_size; ++index)
  {
    if (i_data[index] != '\n')
      d_tail.push_back(i_data[index]);
    else
    {
      processLine(d_tail);
      d_tail.clear();
    }
  }
}

