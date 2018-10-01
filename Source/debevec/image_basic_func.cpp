/** METU CENG587 Project
  * Author: Necip Fazil Yildiran
  * */

#include"header/image_basic_func.hpp"

#include<vector>
#include<string>
#include<math.h>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>

std::vector<cv::Mat> readImages(char** filePaths, int fileCount)
{
	std::vector<cv::Mat> images;

	for(int i = 0; i < fileCount; i++)
	{
		cv::Mat image = cv::imread(filePaths[i], cv::IMREAD_COLOR);
		
		images.push_back(image);
	}

	return images;
}

std::vector<cv::Mat> readImages(std::vector<std::string> filePaths)
{
	std::vector<cv::Mat> images;

	for(int i = 0; i < (int)filePaths.size(); i++)
	{
		cv::Mat image = cv::imread(filePaths[i], cv::IMREAD_COLOR);

		images.push_back(image);
	}
	
	return images;
}

void splitImageIntoChannels(const cv::Mat & image, cv::Mat & B, cv::Mat & G, cv::Mat & R)
{
    cv::Mat channelArray[3];

    cv::split(image, channelArray);

    // The order shall be BGR
    B = channelArray[0];
    G = channelArray[1];
    R = channelArray[2];
}

cv::Mat mergeColorChannels(const cv::Mat & B, const cv::Mat & G, const cv::Mat & R)
{
    cv::Mat result;

    cv::Mat channels[3] = { B, G, R };

    cv::merge(
        channels,
        3,
        result
    );

    return result;
}

cv::Mat quantizeImage(const cv::Mat & image)
{
    cv::Mat result = image.clone();

    result.convertTo(result, CV_8U, 255.0);

    return result;
}


int suggestResize(const cv::Mat & image)
{
    int numberOfPixels = image.rows * image.cols;
    int suggestedResizeFactor = sqrt(numberOfPixels / 50);
    return suggestedResizeFactor;
}










