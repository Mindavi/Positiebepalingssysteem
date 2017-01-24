#ifndef IMAGEREADER_H_
#define IMAGEREADER_H_

#include "ImageReaderStatus.h"
#include <opencv2/core/mat.hpp>

namespace imagereader {

class ImageReader {
public:
  ImageReader(int print_flag = false);
  virtual ~ImageReader();
  virtual ImageReaderStatus TryDecode(cv::Mat& output);
protected:
  std::vector<char> _data;
  bool _skip = true;
  bool _imgready = false;
  bool _ff = false;
  int _readbytes = -1;
  bool _print_flag = false;
  static const int _buffer_size = 10240;
  char _buffer[_buffer_size];
};

}

#endif /* end of include guard: IMAGEREADER_H_ */
