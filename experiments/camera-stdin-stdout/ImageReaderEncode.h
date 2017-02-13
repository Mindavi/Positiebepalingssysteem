#ifndef IMAGEREADER_ENCODE_H_
#define IMAGEREADER_ENCODE_H_

#include "ImageReader.h"

namespace imagereader {

class ImageReaderEncode : public ImageReader {
public:
  ImageReaderEncode(int print_flag = false);
  virtual ~ImageReaderEncode();
  virtual ImageReaderStatus TryDecode(cv::Mat& output);
private:
  bool _print_flag = false;
};

} // namespace imagereader

#endif
