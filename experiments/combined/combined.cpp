#include <opencv2/highgui.hpp>  // for imshow
#include <opencv2/imgproc.hpp>  // for blur, dilation, erosion
#include <opencv2/video.hpp>    // for backgroundsubtractor
#include <opencv2/videoio.hpp>  // for videocapture

#include <iostream>

void show(std::string title, const cv::Mat& image) {
  cv::imshow(title.c_str(), image);
  char c = static_cast<char>(cv::waitKey(1));
  if (c == 27) exit(0);
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

void findContours(const cv::Mat& image, int camera_number) {
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
  std::cout << camera_number << ":" << static_cast<int>(middle.x) << ","
            << static_cast<int>(middle.y) << std::endl;

  cv::Scalar color = cv::Scalar(255, 255, 255);
  cv::drawContours(drawing, contours, index, color, 2, 8, hierarchy, 0,
                   cv::Point());
  show("contours", drawing);
}

int thread(int camera_number) {
  cv::Mat background;                       // background image
  cv::Ptr<cv::BackgroundSubtractor> pMOG2;  // MOG2 Background subtractor
  int blur_size = 10;
  int erosion_size = 10;
  int dilation_size = 10;
  int learning_rate = 0;

  const int bg_history = 500;
  const int threshold = 16;          // default value
  const bool detectShadows = false;  // non-default

  pMOG2 =
      cv::createBackgroundSubtractorMOG2(bg_history, threshold, detectShadows);

  auto capture = cv::VideoCapture(camera_number);
  std::string control_window_name = "control" + std::to_string(camera_number);
  cv::namedWindow(control_window_name);
  cv::createTrackbar("blur", control_window_name, &blur_size, 20);
  cv::createTrackbar("erosion", control_window_name, &erosion_size, 20);
  cv::createTrackbar("dilation", control_window_name, &dilation_size, 20);
  cv::createTrackbar("learning rate", control_window_name, &learning_rate,
                     learning_rate_divider);

  std::cerr << camera_number << " started\n";
  while (1) {
    cv::Mat image;
    if (!capture.read(image) || image.empty()) {
      continue;
    }
    blur(&image, blur_size);
    erode(&image, erosion_size);
    dilate(&image, dilation_size);
    subtract(pMOG2, &image, &background, learning_rate);
    findContours(background, camera_number);
    show("transformed" + std::to_string(camera_number), background);
  }
}

int main(void) { thread(0); }
