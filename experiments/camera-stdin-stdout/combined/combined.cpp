#include <opencv2/highgui.hpp>  // for imshow
#include <opencv2/videoio.hpp>  // for videocapture
#include <opencv2/video.hpp>  // for backgroundsubtractor
#include <opencv2/imgproc.hpp>  // for blur, dilation, erosion
#include <opencv2/features2d.hpp>  // for simpleblobdetector

#include <iostream>

void show(const char* title, const cv::Mat& image) {
    cv::imshow(title, image);
    char c = static_cast<char>(cv::waitKey(1));
    if (c == 27) exit(0);
}

cv::Mat background;  // background image
cv::Ptr<cv::BackgroundSubtractor> pMOG2;  // MOG2 Background subtractor
const int bg_history = 500;
const int threshold = 16;  // default value
const bool detectShadows = false;  // non-default
const char* control_window_name = "control";

const int minimal_area = 200;
const int maximal_area = 500;

int blur_size = 10;
int erosion_size = 10;
int dilation_size = 10;
float learning_rate = -1.0;
const int learning_rate_divider = 10000;

void updateLearningRate(int rate, void*) {
    if (rate == 0) {
        learning_rate = -1.0;  // software auto-decides
        return;
    }
    learning_rate = rate / static_cast<double>(learning_rate_divider);
}

void subtract(cv::Mat* image) {
    pMOG2->apply(*image, background, learning_rate);
}

void blur(cv::Mat* input_output) {
    if (blur_size <= 0) {
        return;
    }
    cv::Size size(blur_size, blur_size);
    cv::blur(*input_output, *input_output, size);
}

void erode(cv::Mat* input_output) {
    if (erosion_size <= 0) {
        return;
    }
    int erosion_type = cv::MORPH_RECT;
    cv::Mat element = cv::getStructuringElement(erosion_type,
        cv::Size(2*erosion_size, 2*erosion_size),
        cv::Point(erosion_size, erosion_size));
    cv::erode(*input_output, *input_output, element);
}

void dilate(cv::Mat* input_output) {
    if (dilation_size <= 0) {
        return;
    }
    int dilation_type = cv::MORPH_RECT;
    cv::Mat element = cv::getStructuringElement(dilation_type,
        cv::Size(2*dilation_size, 2*dilation_size),
        cv::Point(dilation_size, dilation_size));
    cv::dilate(*input_output, *input_output, element);
}

cv::Ptr<cv::SimpleBlobDetector> p_blob;

void detectBlobs(const cv::Mat& image) {
    std::vector<cv::KeyPoint> keypoints;
    p_blob->detect(image, keypoints);

    if (keypoints.size() <= 0) {
        return;
    }
    cv::KeyPoint biggest;


    for (const auto& keypoint : keypoints) {
        if (keypoint.size > biggest.size) {
            biggest = keypoint;
        }
    }
    std::cout << static_cast<int>(biggest.pt.x) << "," << static_cast<int>(biggest.pt.y) << std::endl;
}

void findContours(const cv::Mat& image) {
    cv::Mat canny_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    /// Find contours
    cv::findContours(image,
        contours,
        hierarchy,
        cv::RETR_TREE,
        cv::CHAIN_APPROX_SIMPLE,
        cv::Point(0, 0));

    cv::Mat drawing = cv::Mat::zeros(image.size(), CV_8UC3);
    cv::Scalar color = cv::Scalar(255, 255, 255);

    int index = 0;
    double biggest_area = 0.0;
    for (int i = 0; i < contours.size(); i++) {
        auto area = cv::contourArea(contours[i]);
        if (area > biggest_area) {
            index = i;
            biggest_area = area;
        }
    }

    cv::drawContours(drawing, contours, index, color, 2, 8, hierarchy, 0, cv::Point());

    /// Show in a window
    namedWindow("Contours", cv::WINDOW_AUTOSIZE);
    imshow("Contours", drawing);
}


int main(void) {
    pMOG2 = cv::createBackgroundSubtractorMOG2(bg_history,
        threshold,
        detectShadows);

    auto capture = cv::VideoCapture(0);
    cv::namedWindow(control_window_name);
    cv::createTrackbar("blur", control_window_name, &blur_size, 20);
    cv::createTrackbar("erosion", control_window_name, &erosion_size, 20);
    cv::createTrackbar("dilation", control_window_name, &dilation_size, 20);
    cv::createTrackbar("learning rate",
        control_window_name,
        nullptr,
        learning_rate_divider,
        updateLearningRate);

    cv::waitKey(1);

    cv::SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.filterByCircularity = false;
    params.filterByColor = true;
    params.blobColor = 255;
    params.filterByConvexity = false;
    params.minArea = minimal_area;
    params.maxArea = maximal_area;
    p_blob = cv::SimpleBlobDetector::create(params);


    while (1) {
        cv::Mat image;
        if (!capture.read(image) || image.empty()) {
            continue;
        }
        // show("start", image);
        blur(&image);
        erode(&image);
        dilate(&image);
        subtract(&image);
        findContours(background);
        detectBlobs(background);
        show("transformed", background);
    }
}
