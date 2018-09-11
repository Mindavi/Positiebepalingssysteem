#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>

struct options {
  bool use_url = 0;
  std::string url;
  bool use_camera = 0;
  int camera_id = 0;
  bool view_camera = 0;
  bool verbose = 0;
};

extern struct options options;

#endif  // OPTIONS_H_
