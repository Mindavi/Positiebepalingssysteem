#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include "ImageReader.h"
#include "print_image.h"
#include "Log.h"

// set by --blur or -b
int blur_size = 0;

//set by --verbose or -v
int verbose_flag = 0;

dlog::Log logger;

void blur(cv::Mat& input_output)
{
  cv::Size size(2*blur_size, 2*blur_size);
  cv::blur(input_output, input_output, size);
}

static struct option options[]
{
  {"verbose", no_argument, NULL, 'v'},
  {"help", no_argument, NULL, 'h'},
  {"blur", required_argument, NULL, 'b'},
  {0, 0, 0, 0}
};


static const std::string help_text = ""\
" -h, --help\t\tview this message\n"\
" -v, --verbose\t\tenable verbose mode\n"\
" -b, --blur\tset blur size, must be an integer > 0\n";

static void parse_options(int argc, char* argv[]) {
  while(1)
  {
    int option = getopt_long(argc, argv, "vhb:", options, NULL);
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
      case 'b':
        if (optarg)
        {
          blur_size = std::atoi(optarg);
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
  logger.log("Blur size: " + std::to_string(blur_size));

}


int main(int argc, char* argv[])
{
  parse_options(argc, argv);
  imagereader::ImageReader imagereader;
  cv::Mat source;
  while(1)
  {
    imagereader.Decode(source);
    if (blur_size > 0) blur(source);
    print_image::print_image(source);
  }
}
