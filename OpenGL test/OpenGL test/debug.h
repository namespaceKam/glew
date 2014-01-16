#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>

class DebugLogger
{
public:
  friend DebugLogger& Debug();
  void Print(const std::string& text);
  void CheckGLError();

private:
  std::fstream log;
  DebugLogger();
};

//DebugLogger& Debug();


static DebugLogger& Debug()
{
  static DebugLogger debug;
  return debug;
}

#endif