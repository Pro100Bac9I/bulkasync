#pragma once

#include <memory>
#include <string>

class CommandBlock;

class LineProcessor
{
public:
  LineProcessor(int i_len);
  ~LineProcessor();

  void run();

  void processLine(const char* i_data, size_t i_size);

private:
  void processLine(const std::string &i_line);

private:
  std::shared_ptr<CommandBlock> d_block;
  int d_bracketCounter = 0;
  std::string d_tail;
};
