#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include "ImageReader.h"

// set by --print
static int print_flag = 0;

//set by --verbose
static int verbose_flag = 0;

static struct option options[]
{
  {"print", no_argument, &print_flag, 1},
  {"verbose", no_argument, &verbose_flag, 1},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

static const std::string help_text = ""\
" -h, --help\t\tview this message\n"\
" -p, --print\t\tprint the received data back to standard out\n"\
" -v, --verbose\t\tenable verbose mode\n";


static void parse_options(int argc, char* argv[]) {
  while(1)
  {
    int option = getopt_long(argc, argv, "pvh", options, NULL);
    if (option == -1) break;
    switch(option)
    {
      case 0:
        /* longopt already did something, nothing to be done */
        break;
      case 'p':
        print_flag = true;
        break;
      case 'v':
        verbose_flag = true;
        break;
      case 'h':
        std::clog << help_text;
        exit(EXIT_SUCCESS);
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
  if (verbose_flag)
  {
    std::clog << "Verbose mode activated.\n";
  }
}

using namespace cv;

#define BUFSIZE 10240
int main (int argc, char* argv[])
{
  parse_options(argc, argv);
  dlog::Log::Loglevel log_level = verbose_flag ? dlog::Log::verbose : dlog::Log::none;
  imagereader::ImageReader reader(print_flag, log_level);
  while (1)
  {
    cv::Mat output_frame;
    reader.Decode(output_frame);
    cv::imshow("frame", output_frame);
    cv::waitKey(1);
  }
}
