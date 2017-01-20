#include "ImageReader.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <unistd.h>
#include <iostream>

namespace imagereader {

ImageReader::ImageReader(int print_flag)
  : _print_flag(print_flag)
{}

ImageReader::~ImageReader() {}

ImageReaderStatus ImageReader::TryDecode(cv::Mat& output) {
  ImageReaderStatus status = kNotDone;
  if (_readbytes != 0)
  {
    uchar c;
    _readbytes = read(fileno(stdin), _buffer, _buffer_size);
    // if (verbose_flag) std::clog << "read bytes: " << _readbytes << '\n';

    for(int i = 0; i < _readbytes; i++)
    {
      c = _buffer[i];
      if (_print_flag) std::cout << c;
      if (_ff && c == static_cast<uchar>(0xd8))
      {
        _skip = false;
        _data.push_back(static_cast<uchar>(0xff));
      }
      if (_ff && c == 0xd9)
      {
        _imgready = true;
        _data.push_back(static_cast<uchar>(0xd9));
        _skip = true;
      }
      _ff = (c == 0xff);
      if (!_skip)
      {
        _data.push_back(c);
      }
      if (_imgready)
      {
        if (_data.size() != 0)
        {
          cv::Mat data_mat(_data);
          output = cv::Mat(cv::imdecode(data_mat,1));
          status = !output.empty() ? kImageRead : kEmptyInvalidFrame;
        }
        else
        {
          status = kWarning;
        }
        _imgready = false;
        _skip = true;
        _data.clear();
      }
    }
  }
  else
  {
    status = kZeroByte;
  }
  return status;
}


} // namespace imagereader
