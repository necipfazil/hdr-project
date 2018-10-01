/** METU CENG587 Project
  * Author: Necip Fazil Yildiran
  * */

#include "header/reinhard_tonemapping.hpp"
#include "../debevec/header/image_basic_func.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include <vector>

#define _USE_MATH_DEFINES

using namespace std;
using namespace cv;

Mat getTonemappedColorImg(const Mat & rgbHdrImg, const Mat & luminanceImg, const Mat & tonemappedLum, float s = 1.0f);

Mat localTMO(const Mat & hdrImg, float keyA, float sharpeningFi, float thresholdE)
{
    // get luminance image
    Mat luminanceImg = getLuminanceImage(hdrImg);

    // scale luminance image by key value keyA
    Mat scaledLuminanceImg = scaleLuminanceByKey(luminanceImg, keyA);

    vector<Mat> blurredImgsV1;
    vector<Mat> blurredImgsV2;

    // compute blurred images
    for(int i = 0; i < 8; i++)
    {
        Mat blurredR1, blurredR2;

        int windowSize = getWindowSize(i + 1);

        float sigma = 0.35 * pow(1.6f, i);

        GaussianBlur(luminanceImg, blurredR1, cv::Size(windowSize, windowSize), sigma);
        GaussianBlur(luminanceImg, blurredR2, cv::Size(getWindowSize(i+1), getWindowSize(i+1)), sigma * 1.6);

        // store the results
        blurredImgsV1.push_back(blurredR1);
        blurredImgsV2.push_back(blurredR2);
    }

    // compute center-surround function (as in Equation 7)
    vector<Mat> V = computeCenterSurround(blurredImgsV1, blurredImgsV2, sharpeningFi, keyA);

    // compute V1 (local avg) that is going to be used in equation 9
    // first, initialize the it with the smallest scale in case none of the scales catches it
    Mat localAvg = blurredImgsV1[0].clone();

    for(int x = 0; x < luminanceImg.cols; x++)
    {
        for(int y = 0; y < luminanceImg.rows; y++)
        {

            // if non of the scales would be able to catch the error, set it to the largest one
            int chosenScale = 7;

            // go from smallest to largest. when threshold is exceeded, choose the former scale
            for(int scaleInd = 0; scaleInd < 8; scaleInd++)
            {
                // the value of V2-V1 at this scale
                float el = V[scaleInd].at<float>(y, x);

                if(abs(el) >= thresholdE)
                {
                    // found! choose the former level (if possible)
                    if(scaleInd > 0)
                    {
                        chosenScale = scaleInd - 1;
                    }
                    else
                    {
                        // choose the current
                        chosenScale = scaleInd;
                    }

                    break;
                }
            }

            // set the local average from chosen scale
            localAvg.at<float>(y,x) = blurredImgsV1[chosenScale].at<float>(y,x);
        }
    }

    // now, compute tonemapped luminance image
    Mat localToneMappedLuminanceImg;

    // denominator in Equation 9
    Mat denominator = localAvg + 1.0f;

    cv::divide(
        scaledLuminanceImg,
        denominator,
        localToneMappedLuminanceImg
    );

    // compute local-tone-mapped color image
    Mat coloredLocalTMImg = getTonemappedColorImg(hdrImg, luminanceImg, localToneMappedLuminanceImg);

    return coloredLocalTMImg;

}


int getWindowSize(int scale)
{
    float windowScale = (43.0f / 8.0f);

    int windowSize = windowScale * scale;

    if(!(windowSize % 2))
        windowSize++;

    return windowSize;
}

vector<Mat> computeCenterSurround(const vector<Mat> & blurredImgsV1, const vector<Mat> & blurredImgsV2, float sharpeningFi, float keyA )
{
    vector<Mat> V;

    for(int scaleInd = 0; scaleInd < (int)blurredImgsV1.size(); scaleInd++)
    {
        // V1 - V2
        Mat numerator, denominator, result;

        cv::subtract(
            blurredImgsV1[scaleInd],
            blurredImgsV2[scaleInd],
            numerator
        );

        // the parameter to do normalization as done in equation 7
        float normalizer = (pow(2.0f, sharpeningFi) * keyA) / (getWindowSize(scaleInd + 1) * getWindowSize(scaleInd + 1));

        denominator = blurredImgsV1[scaleInd] + normalizer;

        cv::divide(
            numerator,
            denominator,
            result
        );

        V.push_back(result);
    }

    return V;
}

// color assignment
// s: saturation
Mat getTonemappedColorImg(const Mat & rgbHdrImg, const Mat & luminanceImg, const Mat & tonemappedLum, float s )
{
	// for each color, compute C_out = L_out * ( C_in / L_in ) ^ s
	std::vector<cv::Mat> bgrChannels(3);
	
	cv::split(rgbHdrImg, bgrChannels);
	
	// for each channel, compute the division: C_in / L_in
	for(int i = 0; i < 3; i++)
		cv::divide(
			bgrChannels[i],
			luminanceImg,
			bgrChannels[i]
		);
	
	// for each channel, compute the raise to s
	if(s != 1.0f)
		for(int i = 0; i < 3; i++)
			cv::pow(
				bgrChannels[i],
				s,
				bgrChannels[i]
			);

	// for each channel, element-wise multiplication with L_out
	for(int i = 0; i < 3; i++)
		cv::multiply(
			bgrChannels[i],
			tonemappedLum,
			bgrChannels[i]
		);
	
	// merge channels and return
	Mat result;
	merge(bgrChannels, result);
	return result;
}

// color assignment, overloaded
Mat getTonemappedColorImg(const Mat & rgbHdrImg, const Mat & tonemappedLum, float s = 1.0f)
{
	Mat luminanceImg = getLuminanceImage(rgbHdrImg);
	
	return getTonemappedColorImg(rgbHdrImg, luminanceImg, tonemappedLum, s);

}

Mat globalTMO(const Mat & hdrImg, float keyA, float Lwhite)
{
	Mat LsquareOverLWhite, numerator, denominator, toneMappedLuminanceImg;

	// get luminance image
	Mat luminanceImg = getLuminanceImage(hdrImg);
	
	// scale luminance image by key value keyA
	Mat scaledLuminanceImg = scaleLuminanceByKey(luminanceImg, keyA);
	
	// notice that multiply, add and divide are element-wise operators
	
	// compute LsquareOverLWhite
	cv::multiply(
		scaledLuminanceImg,			// src1
		scaledLuminanceImg,			// src3
		LsquareOverLWhite,			// dst
		1.0 / (Lwhite * Lwhite)		// scale
	);
	
	// compute numerator
	cv::add(
		LsquareOverLWhite,			// src1
		scaledLuminanceImg,			// src2
		numerator					// dst
	);
	
	// compute denominator
	denominator = scaledLuminanceImg + 1;
	
	// compute tone-mapped luminance image
	cv::divide(
		numerator,				// src1
		denominator,			// src2
		toneMappedLuminanceImg	// dst
	);
	
	// compute global tone-mapped color image
	Mat toneMappedColoredImg = getTonemappedColorImg(hdrImg, luminanceImg, toneMappedLuminanceImg);
	
	return toneMappedColoredImg;
}

Mat scaleLuminanceByKey(const Mat & lumImg, float keyA = 0.18f)
{
	if(lumImg.empty() || lumImg.channels() != 1 || lumImg.type() != CV_32FC1)
	{
		cerr << "Error: Incorrect input for scaleLuminanceByKey()" << endl;
		exit(1);
	}

	// get log-average luminance
	float logAvgLum = getLogAvgLuminance(lumImg);
	
	// get the scale factor
	float scaleFactor = keyA / logAvgLum;
	
	// scale and return
	return lumImg * scaleFactor;
	
}

float getLogAvgLuminance(const Mat & lumImg)
{
	if(lumImg.empty() || lumImg.channels() != 1 || lumImg.type() != CV_32FC1)
	{
		cerr << "Error: Incorrect input for getLogLuminanceAvg()" << endl;
		exit(1);
	}
	
	int numOfRows = lumImg.rows;
	int numOfCols = lumImg.cols;
	
	// get log(luminance) image. notice that the base is e
    Mat logLumImg;
	cv::log(lumImg, logLumImg);
	
	
	Mat mask = logLumImg != logLumImg;
	
	// NaN check
	for(int x = 0; x < numOfRows; x++)
	{	
		for(int y = 0; y < numOfCols; y++)
		{
			unsigned char maskVal = mask.at<unsigned char>(x, y);
			if(maskVal != 0x00)
			{
                cout << "Warning: NaN in getLogLuminanceAvg()" << endl;
			}
		}
	}
	
	// sum log(luminances)
	float sum = cv::sum(logLumImg)[0];
	
	// divide the sum by number of pixels
	sum /= numOfRows * numOfCols;
	
	// exponantiate to get the result
	float avg = std::exp(sum);
	
	return avg;
}

Mat getLuminanceImage(const Mat & colorImage)
{
    if(colorImage.empty() || colorImage.channels() != 3 || colorImage.type() != CV_32FC3)
	{
		cerr << "Error: Incorrect input for getLuminanceImage()" << endl;
		exit(1);
	}

    // same resolution but one channnel, which will carry the luminance value
    Mat luminanceImage;
    Mat B, G, R;
    splitImageIntoChannels(colorImage, B, G, R);

    luminanceImage = 0.2126 * R + 0.7152 * G + 0.0722 * B; //0.27f * R + 0.67f * G + 0.06f * B;

    return luminanceImage;
}

bool checkInput(const Mat & inputHdrImage)
{
    if(inputHdrImage.empty())
    {
        cerr << "Error: Couldn't read the input file" << endl;
        return false;
    }

    // type check: CV_32F
    else if(inputHdrImage.type() != CV_32FC3)
    {
        cerr << "Error: Incorrect image type. Was waiting for CV_32FC3" << endl;
        return false;
    }

    else if(!inputHdrImage.isContinuous())
    {
        cout << "Error: Not continuous!" << endl;
        return false;
    }

    return true;
}
