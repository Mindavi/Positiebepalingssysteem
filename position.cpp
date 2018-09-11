#include <unistd.h>
#include <csignal>
#include <cstddef>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>  // for imshow
#include <opencv2/imgproc.hpp>  // for blur, dilation, erosion
#include <opencv2/video.hpp>    // for backgroundsubtractor
#include <opencv2/videoio.hpp>  // for videocapture
#include <stdexcept>
#include <string>
#include "log.h"
#include "options.h"

#define VERSION VERSION_STR(EXT_VER)
#define VERSION_STR(X) _VERSION_STR(X)
#define _VERSION_STR(X) #X

const int escape_key = 27;

const char* version = "Version (" VERSION ")";

const char* help_text =
    "\t-u <url/file>: read from url or file\n"
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
  auto mutual_exclusive_options_count = options.use_camera + options.use_url;
  if (mutual_exclusive_options_count > 1) {
    std::cerr
        << "ERROR: You can only use one of camera or url/file. Exiting...\n";
    exit(EXIT_FAILURE);
  }
  if (!(options.use_camera || options.use_url)) {
    std::cerr << "ERROR: Please select camera or url/file mode. Exiting...\n";
    exit(EXIT_FAILURE);
  }
}

void show(std::string title, const cv::Mat& image) {
  if (options.view_camera) {
    cv::imshow(title.c_str(), image);
    char c = static_cast<char>(cv::waitKey(1));
    if (c == 27) exit(0);
  }
}

const auto learning_rate_divider = 10000;

void subtract(cv::Ptr<cv::BackgroundSubtractor> pMOG2, cv::Mat* image,
              cv::Mat* background, int learning_rate) {
  auto rate = learning_rate / static_cast<double>(learning_rate_divider);
  if (learning_rate <= 0) {
    rate = -1.0;
  }
  pMOG2->apply(*image, *background, rate);
}

void blur(cv::Mat* input_output, int blur_size) {
  if (blur_size <= 0) {
    return;
  }
  cv::blur(*input_output, *input_output, cv::Size(blur_size, blur_size));
}

void erode(cv::Mat* input_output, int erosion_size) {
  if (erosion_size <= 0) {
    return;
  }
  int erosion_type = cv::MORPH_RECT;
  cv::Mat element = cv::getStructuringElement(
      erosion_type, cv::Size(2 * erosion_size, 2 * erosion_size),
      cv::Point(erosion_size, erosion_size));
  cv::erode(*input_output, *input_output, element);
}

void dilate(cv::Mat* input_output, int dilation_size) {
  if (dilation_size <= 0) {
    return;
  }
  int dilation_type = cv::MORPH_RECT;
  cv::Mat element = cv::getStructuringElement(
      dilation_type, cv::Size(2 * dilation_size, 2 * dilation_size),
      cv::Point(dilation_size, dilation_size));
  cv::dilate(*input_output, *input_output, element);
}

cv::Point2f findContourMiddle(const std::vector<cv::Point>& contour) {
  /// Get the moments
  cv::Moments moments = cv::moments(contour, false);
  if (moments.m00 == 0) {
    return cv::Point2f(-1, -1);
  }

  ///  Get the mass centers:
  cv::Point2f mc =
      cv::Point2f(moments.m10 / moments.m00, moments.m01 / moments.m00);
  return mc;
}

void findContours(const cv::Mat& image) {
  cv::Mat canny_output;
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;

  /// Find contours
  cv::findContours(image, contours, hierarchy, cv::RETR_TREE,
                   cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

  if (contours.size() < 1) {
    return;
  }

  cv::Mat drawing = cv::Mat::zeros(image.size(), CV_8UC3);

  int index = 0;
  double biggest_area = 0.0;
  for (size_t i = 0; i < contours.size(); i++) {
    auto area = cv::contourArea(contours[i]);
    if (area > biggest_area) {
      index = i;
      biggest_area = area;
    }
  }

  auto middle = findContourMiddle(contours[index]);
  std::cout << static_cast<int>(middle.x) << "," << static_cast<int>(middle.y)
            << std::endl;

  cv::Scalar color = cv::Scalar(255, 255, 255);
  cv::drawContours(drawing, contours, index, color, 2, 8, hierarchy, 0,
                   cv::Point());
  show("contours", drawing);
}

void loop(cv::VideoCapture* capture) {
  cv::Mat background;                       // background image
  cv::Ptr<cv::BackgroundSubtractor> pMOG2;  // MOG2 Background subtractor
  int blur_size = 10;
  int erosion_size = 10;
  int dilation_size = 10;
  int learning_rate = 50;

  const int bg_history = 500;
  const int threshold = 16;          // default value
  const bool detectShadows = false;  // non-default

  pMOG2 =
      cv::createBackgroundSubtractorMOG2(bg_history, threshold, detectShadows);

  if (options.view_camera) {
    std::string control_window_name = "control";
    cv::namedWindow(control_window_name);
    cv::createTrackbar("blur", control_window_name, &blur_size, 20);
    cv::createTrackbar("erosion", control_window_name, &erosion_size, 20);
    cv::createTrackbar("dilation", control_window_name, &dilation_size, 20);
    cv::createTrackbar("learning rate", control_window_name, &learning_rate,
                       learning_rate_divider);
  }

  cv::Mat image;

  if (!capture->read(image) || image.empty()) {
    std::cout << "Invalid input received" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "[" << image.rows << "x" << image.cols << "]" << std::endl;
  while (run) {
    if (!capture->read(image) || image.empty()) {
      exit(0);
      continue;
    }
    show("original", image);
    blur(&image, blur_size);
    erode(&image, erosion_size);
    dilate(&image, dilation_size);
    subtract(pMOG2, &image, &background, learning_rate);
    findContours(background);
    show("transformed", background);
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
    std::cerr << "Invalid option\n";
    exit(2);
  }
  loop(&capture);
  log("Exiting...");
  return EXIT_SUCCESS;
}
