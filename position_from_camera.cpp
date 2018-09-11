#include <unistd.h>
#include <csignal>
#include <cstddef>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdexcept>
#include <string>
#include "helpers.h"
#include "options.h"

#define VERSION VERSION_STR(EXT_VER)
#define VERSION_STR(X) _VERSION_STR(X)
#define _VERSION_STR(X) #X

const int escape_key = 27;

const char* version = "Version (" VERSION ")";

const char* help_text =
    "\t-u <url>: read from url\n"
    "\t-c <camera-id>: use camera_id\n"
    "\t-o: view camera output\n"
    "\t-v: verbose mode\n"
    "\t-h: view this help text\n"
    "\t-V: view version\n";

struct options options;

sig_atomic_t run = true;
void termination_signal(int) { run = false; }

void get_and_set_options(int argc, char* argv[]) {
  int c;
  while ((c = getopt(argc, argv, "hu:c:ovV")) != -1) {
    switch (c) {
      case 'u':
        options.use_url = true;
        options.url = optarg;
        break;
      case 'c':
        options.use_camera = true;
        try {
          options.camera_id = std::stoi(optarg);
        } catch (std::invalid_argument& e) {
          std::cerr << "ERROR: invalid argument given: " << e.what()
                    << std::endl;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range& e) {
          std::cerr << "ERROR: out of range argument given: " << e.what()
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        break;
      case 'o':
        options.view_camera = true;
        break;
      case 'v':
        options.verbose = true;
        log("Verbose logging enabled");
        break;
      case 'V':
        std::clog << version << std::endl;
        exit(EXIT_SUCCESS);
        break;
      case 'h':
        std::clog << help_text << std::endl;
        exit(EXIT_SUCCESS);
        break;
      case '?':
        std::cerr << help_text << std::endl;
        exit(EXIT_FAILURE);
        break;
      default:
        abort();
        break;
    }
  }
  if (options.use_camera && options.use_url) {
    std::cerr << "ERROR: You can only use camera or url, not both. Exiting..."
              << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!(options.use_camera || options.use_url)) {
    std::cerr << "ERROR: Please select camera or url mode. Exiting..."
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

int get_largest_contour(const cv::Mat frame,
                        std::vector<cv::Point>& largest_contour) {
  if (frame.empty()) {
    return -1;
  }
}

int main(int argc, char* argv[]) {
  signal(SIGINT, termination_signal);
  signal(SIGTERM, termination_signal);
  get_and_set_options(argc, argv);
  cv::VideoCapture capture;
  if (options.use_camera) {
    log("Using camera with id " + std::to_string(options.camera_id));
    capture.open(options.camera_id);
  } else if (options.use_url) {
    log("Using url with link " + options.url);
    capture.open(options.url);
  } else {
    abort();
  }
  log("Starting read loop...");
  cv::Mat frame;
  while (run) {
    capture >> frame;
    if (frame.empty()) {
      log("Empty frame received");
      continue;
    }
    if (options.view_camera) {
      cv::imshow("Video", frame);
      if (cv::waitKey(10) == escape_key) {
        run = false;
        // raise(SIGINT);
      }
    }
  }
  log("Exiting...");
  return EXIT_SUCCESS;
}
