#ifndef HELPERS_H_
#define HELPERS_H_

#include <string>
#include "options.h"

void log(std::string text) {
  if (options.verbose) {
    std::clog << text << std::endl;
  }
}

#endif
