#include <iostream>
#include "helpers.h"
#include "ImageProcessor.h"
#include <opencv2/imgproc/imgproc.hpp>

int ImageProcessor::preprocess_frame(cv::InputOutputArray& frame)
{
  int thresh_sens = 170;
  int blur_sz = 3;

  if (frame.empty())
  {
    return -1;
  }

  cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
  cv::blur(frame, frame, cv::Size(blur_sz, blur_sz));
  
  const int max_sens = 255;
  cv::threshold(frame, frame, thresh_sens, max_sens, cv::THRESH_BINARY);

  return 0;
 
}
