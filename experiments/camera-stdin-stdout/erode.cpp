#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include "ImageReader.h"
#include "print_image.h"
#include "Log.h"

//set by --erode or -e
int erosion_size = 0;

//set by --verbose or -v
int verbose_flag = 0;

dlog::Log logger;

void erode(cv::Mat& input_output)
{
  int erosion_type = cv::MORPH_RECT;
  cv::Mat element = cv::getStructuringElement(erosion_type,
    cv::Size(2*erosion_size, 2*erosion_size),
    cv::Point(erosion_size, erosion_size));
  cv::erode(input_output, input_output, element);
}

static struct option options[]
{
  {"verbose", no_argument, NULL, 'v'},
  {"help", no_argument, NULL, 'h'},
  {"erode", required_argument, NULL, 'e'},
  {0, 0, 0, 0}
};


static const std::string help_text = ""\
" -h, --help\t\tview this message\n"\
" -v, --verbose\t\tenable verbose mode\n"\
" -e, --erode\tset erosion size, must be an integer > 0\n";

static void parse_options(int argc, char* argv[]) {
  while(1)
  {
    int option = getopt_long(argc, argv, "vhe:", options, NULL);
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
      case 'e':
        if (optarg)
        {
          erosion_size = std::atoi(optarg);
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
  logger.log("Erosion: " + std::to_string(erosion_size));
}


int main(int argc, char* argv[])
{
  parse_options(argc, argv);
  imagereader::ImageReader imagereader;
  cv::Mat source;
  while(1)
  {
    imagereader.Decode(source);
    if (erosion_size > 0) erode(source);
    print_image::print_image(source);
  }
}
