#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " {input_image} {template_image}" << std::endl;
        return 0;
    }

    const std::string input_image_file(argv[1]);
    const std::string template_image_file(argv[2]);

    // Read input and template images
    cv::Mat userImg = cv::imread("../../" + input_image_file);
    cv::Mat templateImg = cv::imread("../../" + template_image_file);

    // Check if images loaded
    if (userImg.empty() || templateImg.empty())
    {
        std::cerr << "Cannot load images" << std::endl;
        return -1;
    }

    int WIDTH_CARD = getWidthCard();
    int HEIGHT_CARD = getHeightCard();

    cv::Mat grayImg;
    cv::cvtColor(userImg, grayImg, cv::COLOR_BGR2GRAY);

    cv::Mat blurredImg;
    cv::GaussianBlur(grayImg, blurredImg, cv::Size(3, 3), 0);

    cv::Mat edges;
    cv::Canny(blurredImg, edges, 100, 200);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat frameDial;
    cv::dilate(edges, frameDial, kernel, cv::Point(-1, -1), 2);

    cv::Mat frameThreshold;
    cv::erode(frameDial, frameThreshold, kernel, cv::Point(-1, -1), 1);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(frameThreshold.clone(), contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat contoursImg = userImg.clone();
    cv::drawContours(contoursImg, contours, -1, cv::Scalar(0, 255, 0), 10);

    auto cardInfo = biggestContour(contours);
    std::vector<cv::Point> corners = cardInfo.first;

    cv::Mat biggestContourImg = userImg.clone();
    if (corners.size() == 4)
    {
        corners = reorderCorners(corners);
        drawRectangle(biggestContourImg, corners);
    }

    cv::Mat warpedImg;
    if (corners.size() == 4)
    {
        warpedImg = warpCard(userImg, corners);
    }
    else
    {
        warpedImg = cv::Mat::zeros(HEIGHT_CARD, WIDTH_CARD, CV_8UC3);
    }

    cv::resize(userImg, userImg, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(grayImg, grayImg, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(blurredImg, blurredImg, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(edges, edges, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(frameDial, frameDial, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(frameThreshold, frameThreshold, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(contoursImg, contoursImg, cv::Size(WIDTH_CARD, HEIGHT_CARD));
    cv::resize(biggestContourImg, biggestContourImg, cv::Size(WIDTH_CARD, HEIGHT_CARD));

    cv::Mat blank = cv::Mat::zeros(HEIGHT_CARD, WIDTH_CARD, CV_8UC3);

    std::vector<std::vector<cv::Mat>> imgArr = {
        {userImg, grayImg, blurredImg, edges, frameDial},
        {frameThreshold, contoursImg, biggestContourImg, warpedImg, blank}};

    cv::Mat pipeline = displayImage(imgArr);
    cv::imshow("card", pipeline);
    cv::waitKey(0);

    return 0;
}