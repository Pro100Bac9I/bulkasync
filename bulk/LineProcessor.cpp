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

void LineProcessor::run()
{
  std::string line;

  while (std::getline(std::cin, line))
    processLine(line);

  d_block->setStatus(Status::endBlock);
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

