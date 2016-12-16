#ifndef HELPERS_H_
#define HELPERS_H_

#include <string>

struct options {
  bool use_url = 0;
  std::string url;
  bool use_camera = 0;
  int camera_id = 0;
  bool view_camera = 0;
  bool verbose = 0;
};

void log(std::string text, struct options opts) {
  if (opts.verbose)
  {
    std::clog << text << std::endl;
  }
}

#endif
