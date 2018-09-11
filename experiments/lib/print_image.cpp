#include "print_image.h"
#include <opencv2/imgcodecs.hpp>
#include <iostream>

namespace print_image {

void print_image(const cv::Mat& image)
{
  std::vector<uchar> buffer;
  cv::imencode(".jpg", image, buffer);
  for (auto datapoint = buffer.begin(); datapoint != buffer.end(); ++datapoint)
  {
    std::cout << *datapoint;
  }
}

}
