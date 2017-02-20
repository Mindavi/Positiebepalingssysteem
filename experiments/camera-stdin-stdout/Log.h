#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

namespace dlog {

class Log {
public:
  enum Loglevel {
    none,
    verbose
  };
  Log(Loglevel log_level);
  Log();
  virtual ~Log();
  virtual void log(std::string message); // for verbose logging
  virtual void log(std::string message, Loglevel log_level);
  virtual void setLevel(Loglevel log_level);
private:
  Loglevel m_log_level;
};

} // namespace dlog

#endif /* end of include guard: LOGGER_H_ */
