#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <getopt.h>
#include "ImageReader.h"

//set by --verbose
static int verbose_flag = 0;

int main()
{
  cv::Mat background; // background image
  cv::Ptr<cv::BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
  imagereader::ImageReader reader;

  cv::Mat frame;

  int history = 500; // default value
  int threshold = 16; // default value
  bool detectShadows = false; // non-default
  pMOG2 = cv::createBackgroundSubtractorMOG2(history, threshold, detectShadows); // create bg subtractor object

  while (true)
  {
    if (reader.TryDecode(frame) == imagereader::ImageReaderStatus::kImageRead)
    {
      pMOG2->apply(frame, background);
      std::vector<uchar> buffer;
      cv::imencode(".jpg", background, buffer);
      for (auto datapoint = buffer.begin(); datapoint != buffer.end(); ++datapoint)
      {
        std::cout << *datapoint;
      }
    }
  }

}
