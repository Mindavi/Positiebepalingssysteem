#include "ImageReaderEncode.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <unistd.h>
#include <iostream>

namespace imagereader {

ImageReaderEncode::ImageReaderEncode(int print_flag)
 : ImageReader(print_flag) {}

ImageReaderEncode::~ImageReaderEncode() {}

ImageReaderStatus ImageReaderEncode::TryDecode(cv::Mat& output) {
  ImageReaderStatus status = kNotDone;
  if (_readbytes != 0)
  {
    uchar c;
    _readbytes = read(fileno(stdin), _buffer, _buffer_size);

    for(int i = 0; i < _readbytes; i++)
    {
      c = _buffer[i];
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
          if (_print_flag) {
            std::vector<uchar> buffer;
            cv::imencode("jpg", output, buffer);
            for (auto it = buffer.begin(); it != buffer.end(); ++it)
            {
              std::cout << *it;
            }
          }
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
