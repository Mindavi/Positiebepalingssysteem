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
        int x, y;
        if (sscanf(input.c_str(), "%d,%d", &x, &y) != 2) {
            continue;
        }
        std::cout << x << ":" << y << std::endl;
        image = black;
        cv::circle(image, cv::Point(x, 240), 20, white, -1);
        cv::imshow("circle", image);
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 27) exit(0);
    }
}
