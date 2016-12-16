#ifndef IMAGEPROCESSOR_H_
#define IMAGEPROCESSOR_H_

#include <opencv2/core/core.hpp>

class ImageProcessor 
{
  public:
    int preprocess_frame(cv::InputOutputArray& frame); 
};

#endif

