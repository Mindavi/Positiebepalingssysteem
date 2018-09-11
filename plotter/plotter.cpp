#include <iostream>
#include <iterator>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(void) {
  cv::Scalar black(0, 0, 0);
  cv::Scalar white(255, 255, 255);
  std::string input;

  std::getline(std::cin, input);
  if (std::cin.eof()) {
    exit(0);
  }
  int width, height;
  if (sscanf(input.c_str(), "[%dx%d]", &width, &height) != 2) {
    std::cout << "Invalid input for [WxH]:" << input << std::endl;
    exit(1);
  }
  cv::Mat image(width, height, CV_8U);

  while (1) {
    std::getline(std::cin, input);
    if (std::cin.eof()) {
      exit(0);
    }
    int x, y;
    if (sscanf(input.c_str(), "%d,%d", &x, &y) != 2) {
      std::cout << "Invalid input:" << input << std::endl;
      continue;
    }
    image = black;
    if (x >= 0 && y >= 0) {
      cv::circle(image, cv::Point(x, y), 20, white, -1);
    }
    std::string window_name = "plot";
    cv::putText(image, std::to_string(x) + ',' + std::to_string(y),
                cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(200, 200, 250));
    cv::imshow(window_name.c_str(), image);
    char c = static_cast<char>(cv::waitKey(10));
    if (c == 27) exit(0);
  }
}
