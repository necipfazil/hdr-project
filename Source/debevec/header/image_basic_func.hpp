/** METU CENG587 Project
  * Author: Necip Fazil Yildiran
  * Contact: necip.yildiran@ceng.metu.edu.tr
  * */

#ifndef __IMAGE_BASIC_FUNC_H__
#define __IMAGE_BASIC_FUNC_H__

#include<vector>
#include<string>
#include<opencv2/core.hpp>

std::vector<cv::Mat> readImages(std::vector<std::string> filePaths);

std::vector<cv::Mat> readImages(char** filePaths, int fileCount);

void splitImageIntoChannels(const cv::Mat & image, cv::Mat & B, cv::Mat & G, cv::Mat & R);

cv::Mat mergeColorChannels(const cv::Mat & B, const cv::Mat & G, const cv::Mat & R);

// given image that holds floats of range [0-1], maps it to an image of range [0-255]
cv::Mat quantizeImage(const cv::Mat & image);

// given the Mat, suggests resize factor such that the input image would downsample to 50 pixels when resize applied
int suggestResize(const cv::Mat & image);

#endif
