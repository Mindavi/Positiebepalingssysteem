#ifndef IMAGEREADER_H_
#define IMAGEREADER_H_

#include "ImageReaderStatus.h"
#include "Log.h"
#include <opencv2/core/mat.hpp>

namespace imagereader {

class ImageReader {
public:
  ImageReader(bool print_flag = false, dlog::Log::Loglevel log_level = dlog::Log::none);
  virtual ~ImageReader();
  virtual ImageReaderStatus TryDecode(cv::Mat& output_image);
  virtual void Decode(cv::Mat& output_image);
private:
  std::vector<char> _data;
  bool _skip = true;
  bool _imgready = false;
  bool _ff = false;
  int _readbytes = -1;
  bool _print_flag = false;
  dlog::Log _log;
  static const int _buffer_size = 10240;
  char _buffer[_buffer_size];
};

}

#endif /* end of include guard: IMAGEREADER_H_ */
