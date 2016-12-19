#ifndef HELPERS_H_
#define HELPERS_H_

#include <string>
#include "options.h"

void log(std::string text) {
  if (options.verbose)
  {
    std::clog << text << std::endl;
  }
}

void view(const cv::Mat frame, std::string title) {
  if (options.view_camera) {
    cv::imshow(title, frame);
    cv::waitKey(1); // should be done, to show the frame (might slow the program down a little though, but it's debug output anyway)
  }
}
#endif
