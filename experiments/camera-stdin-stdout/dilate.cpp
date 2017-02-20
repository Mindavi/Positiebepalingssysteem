#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include "ImageReader.h"
#include "print_image.h"
#include "Log.h"

// set by --dilate or -d
int dilation_size = 0;

//set by --verbose or -v
int verbose_flag = 0;

dlog::Log logger;

void dilate(cv::Mat& input_output)
{
  int dilation_type = cv::MORPH_RECT;
  cv::Mat element = cv::getStructuringElement(dilation_type,
    cv::Size(2*dilation_size, 2*dilation_size),
    cv::Point(dilation_size, dilation_size));
  cv::dilate(input_output, input_output, element);
}

static struct option options[]
{
  {"verbose", no_argument, NULL, 'v'},
  {"help", no_argument, NULL, 'h'},
  {"dilate", required_argument, NULL, 'd'},
  {0, 0, 0, 0}
};


static const std::string help_text = ""\
" -h, --help\t\tview this message\n"\
" -v, --verbose\t\tenable verbose mode\n"\
" -d, --dilate\tset dilation size, must be an integer > 0\n";

static void parse_options(int argc, char* argv[]) {
  while(1)
  {
    int option = getopt_long(argc, argv, "vhd:", options, NULL);
    if (option == -1) break;
    switch(option)
    {
      case 0:
        /* longopt already did something, nothing to be done */
        break;
      case 'v':
        verbose_flag = true;
        break;
      case 'h':
        std::clog << help_text;
        exit(EXIT_SUCCESS);
        break;
      case 'd':
        if (optarg)
        {
          dilation_size = std::atoi(optarg);
        }
        break;
      case '?':
        /* getopt_long prints an error message */
        std::clog << help_text;
        exit(EXIT_FAILURE);
        break;
      default:
        abort();
    }
  }
  dlog::Log::Loglevel log_level = verbose_flag ? dlog::Log::verbose : dlog::Log::none;
  logger = dlog::Log(log_level);
  logger.log("Verbose mode activated.");
  logger.log("Dilation: " + std::to_string(dilation_size));

}


int main(int argc, char* argv[])
{
  parse_options(argc, argv);
  imagereader::ImageReader imagereader;
  cv::Mat source;
  while(1)
  {
    imagereader.Decode(source);
    if (dilation_size > 0) dilate(source);
    print_image::print_image(source);
  }
}
