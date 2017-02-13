#include "ImageReaderEncode.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <unistd.h>
#include <iostream>

namespace imagereader {

ImageReaderEncode::ImageReaderEncode(int print_flag)
 : ImageReader(print_flag), _print_flag(print_flag) {}

ImageReaderEncode::~ImageReaderEncode() {}

ImageReaderStatus ImageReaderEncode::TryDecode(cv::Mat& output) {
  ImageReaderStatus status = ImageReader::TryDecode(output);
  if (_print_flag && status == ImageReaderStatus::kImageRead) 
  {
    std::vector <uchar> buffer;
    cv::imencode(".jpg", output, buffer);
    for (auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      std::cout << *it;
    }
  }
  return status;
}

} // namespace imagereader
