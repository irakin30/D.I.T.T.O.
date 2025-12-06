#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <utility>

// Get card dimensions
int getWidthCard();
int getHeightCard();

// Find the biggest contour
std::pair<std::vector<cv::Point>, double> biggestContour(const std::vector<std::vector<cv::Point>> &contours);

// Reorder corners to [topLeft, topRight, bottomLeft, bottomRight]
std::vector<cv::Point> reorderCorners(std::vector<cv::Point> corners);

// Draw rectangle from four corner points
void drawRectangle(cv::Mat &image, const std::vector<cv::Point> &corners);

// Warp card from image using perspective transform
cv::Mat warpCard(const cv::Mat &image, const std::vector<cv::Point> &corners);

// Create the grid image
cv::Mat displayImage(const std::vector<std::vector<cv::Mat>> &imgArr);

#endif // UTILS_H