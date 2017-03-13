#include <getopt.h>
#include <opencv2/features2d.hpp>
#include <iostream>

#include "ImageReader.h"
#include "print_image.h"
#include "Log.h"

//set by --verbose or -v
static int verbose_flag = 0;

// set by --min_area or -a
static int minimal_area = 50;

static dlog::Log logger;

static struct option options[]
{
  {"help", no_argument, NULL, 'h'},
  {"verbose", no_argument, &verbose_flag, 1},
  {"min_area", required_argument, NULL, 'a'},
  {0, 0, 0, 0}
};

static const std::string help_text = ""\
" -h, --help\t\tview this message\n"\
" -v, --verbose\t\tenable verbose mode\n"\
" -a, --min_area\tset minimal blob area, should be > 0 [default is 50]\n";

static void parse_options(int argc, char* argv[]) {
  while(1)
  {
    int option = getopt_long(argc, argv, "hva:", options, NULL);
    if (option == -1) break;
    switch(option)
    {
      case 0:
        /* longopt already did something, nothing to be done */
        break;
      case 'h':
        std::clog << help_text;
        exit(EXIT_SUCCESS);
        break;
      case 'v':
        verbose_flag = true;
        break;
      case 'a':
        if (optarg)
        {
          int min_area = std::atoi(optarg);
          if (min_area > 0)
          {
            minimal_area = min_area;
          }
          else
          {
            std::clog << "Invalid minimal area!\n";
            exit(EXIT_FAILURE);
          }
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
  logger.log("Minimal area set to " + std::to_string(minimal_area));
}




int main(int argc, char* argv[])
{
  parse_options(argc, argv);
  cv::Mat frame;
  imagereader::ImageReader reader;

  cv::SimpleBlobDetector::Params params;
  params.filterByArea = true;
  params.filterByCircularity = false;
  params.filterByColor = true;
  params.blobColor = 255;
  params.filterByConvexity = false;
  params.minArea = minimal_area;
  cv::Ptr<cv::SimpleBlobDetector> p_blob = cv::SimpleBlobDetector::create(params);

  while (true)
  {
    reader.Decode(frame);

    // Detect blobs.
    std::vector<cv::KeyPoint> keypoints;
    p_blob->detect( frame, keypoints);

    // Draw detected blobs as red circles.
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
    cv::Mat im_with_keypoints;
    drawKeypoints( frame, keypoints, im_with_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

    print_image::print_image(im_with_keypoints);
  }

  return 0;
}
