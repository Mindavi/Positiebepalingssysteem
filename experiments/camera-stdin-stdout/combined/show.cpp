#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <iterator>

const int width = 640;
const int height = 480;

int main(void) {
    std::string input;
    cv::Mat image(height, width, CV_8U);
    cv::Scalar black(0, 0, 0);
    cv::Scalar white(255, 255, 255);


    while (1) {
        std::getline(std::cin, input);
        if (std::cin.eof()) {
            exit(0);
        }
        int camera_number, x, y;
        if (sscanf(input.c_str(), "%d:%d,%d", &camera_number, &x, &y) != 3) {
            std::cout << "Invalid input:" << input << std::endl;
            continue;
        }
        image = black;
        cv::circle(image, cv::Point(x, y), 20, white, -1);
        std::string window_name = "circle" + std::to_string(camera_number);
        cv::putText(image, std::to_string(camera_number), cv::Point(30, 30),
          cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(200, 200, 250));
        cv::imshow(window_name.c_str(), image);
        char c = static_cast<char>(cv::waitKey(10));
        if (c == 27) exit(0);
    }
}
