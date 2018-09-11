#include "Log.h"
#include <iostream>

namespace dlog {

Log::Log(Loglevel log_level)
  : m_log_level(log_level) {}

Log::Log()
  : m_log_level(verbose) {}

Log::~Log() {}

void Log::log(std::string message, Loglevel log_level)
{
  if (log_level == m_log_level)
  {
    std::clog << message << std::endl;
  }
}

void Log::log(std::string message)
{
  log(message, verbose);
}

void Log::setLevel(Loglevel log_level)
{
  m_log_level = log_level;
}

} // namespace dlog
