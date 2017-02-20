#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <getopt.h>
#include <cstdlib> // for eg strtod
#include "ImageReader.h"
#include "print_image.h"

//set by --verbose or -v
static int verbose_flag = 0;

//set by --learning_rate or -l
static double learning_rate = -1.0; // automatically between 0 and 1 chosen by algorithm

//set by --history or -p
static int bg_history = 500;

static dlog::Log logger;

static struct option options[]
{
  {"verbose", no_argument, &verbose_flag, 1},
  {"help", no_argument, NULL, 'h'},
  {"learning_rate", required_argument, NULL, 'l'},
  {"history", required_argument, NULL, 'p'},
  {0, 0, 0, 0}
};

static const std::string help_text = ""\
" -h, --help\t\tview this message\n"\
" -v, --verbose\t\tenable verbose mode\n"\
" -l, --learning_rate\tset learning rate (double), should be between 0 and 1, -1 for automatic decision\n"\
" -p, --history\t\tset history [default = 500], should be > 0\n";

static void parse_options(int argc, char* argv[]) {
  while(1)
  {
    int option = getopt_long(argc, argv, "vhl:p:", options, NULL);
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
      case 'l':
        if (optarg)
        {
          double rate = std::strtod(optarg, NULL);
          if (rate >= -1.0 && rate <= 1.0)
          {
            learning_rate = rate;
          }
          else
          {
            std::clog << "Invalid learning rate!\n";
            exit(EXIT_FAILURE);
          }
        }
        break;
      case 'p':
        if (optarg)
        {
          int history = std::atoi(optarg);
          if (history <= 0)
          {
            std::clog << "Invalid history!\n";
            exit(EXIT_FAILURE);
          }
          bg_history = history;
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
  logger.log("Learning rate set to " + std::to_string(learning_rate));
  logger.log("History set to " + std::to_string(bg_history));
}

int main(int argc, char* argv[])
{
  parse_options(argc, argv);

  cv::Mat background; // background image
  cv::Ptr<cv::BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
  imagereader::ImageReader reader;

  cv::Mat frame;


  int threshold = 16; // default value
  bool detectShadows = false; // non-default
  pMOG2 = cv::createBackgroundSubtractorMOG2(bg_history, threshold, detectShadows); // create bg subtractor object
  logger.log(std::string("BackgroundSubtractor created:"\
  "\n history: " + std::to_string(bg_history) + \
  "\n threshold: " + std::to_string(threshold) + \
  "\n detectShadows: " + std::to_string(detectShadows) + '\n'));
  while (true)
  {
    reader.Decode(frame);
    pMOG2->apply(frame, background, learning_rate);
    print_image::print_image(background);
  }
}
