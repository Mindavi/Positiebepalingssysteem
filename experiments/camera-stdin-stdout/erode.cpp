#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include "ImageReader.h"
#include "print_image.h"

int erosion_size = 20;
//int dilation_size = 0;

int erode(cv::Mat& input_output)
{
  int erosion_type = cv::MORPH_RECT;
  cv::Mat element = cv::getStructuringElement(erosion_type,
    cv::Size(2*erosion_size, 2*erosion_size),
    cv::Point(erosion_size, erosion_size));
  cv::erode(input_output, input_output, element);
  return 0;
}

int main(/*int argc, char* argv[]*/)
{
  imagereader::ImageReader imagereader;
  cv::Mat source;
  while(1)
  {
    imagereader::ImageReaderStatus status = imagereader.TryDecode(source);

    switch (status)
    {
      case imagereader::ImageReaderStatus::kZeroByte:
        std::clog << "Zero byte received, work is done.\n";
        exit(EXIT_SUCCESS);
    }
    if (status != imagereader::ImageReaderStatus::kImageRead)
    {
      continue;
    }
    erode(source);
    print_image::print_image(source);
  }
}
