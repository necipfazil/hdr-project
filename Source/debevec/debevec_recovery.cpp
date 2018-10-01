/** METU CENG587 Project
  * Author: Necip Fazil Yildiran
  * */

#include"header/debevec_recovery.hpp"
#include"header/image_basic_func.hpp"

#include<iostream>
#include<string>
#include<vector>

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

/////////////////////////
// DECLARATIONS: START //

Mat createHdrFromBracketedExposureSequence_Debevec
(
	vector<Mat> images,
	//float smoothnessLambda = 1.0f,
	float smoothnessLambda,
	//float resizingFactor = 1.0f
	float resizingFactor
);

void recoverResponseCurve
(
	vector<Mat> & images,
	float smoothnessLambda,
	float resizingFactor,
	vector<float> & B_gCurve,
	vector<float> & G_gCurve,
	vector<float> & R_gCurve
);

Mat recoverColorChannel
(
	const vector<float> & gCurve,
	const vector<Mat> & Z,
	const vector<int> & logDelta_t
);

void _recoverSingleChannelCurve
(
	const vector<Mat> & Z,
	float smoothnessLambda, // 20.0f?
	vector<float> & gCurve
);

//void splitImageIntoChannels(const Mat & image, Mat & B, Mat & G, Mat & R);

void splitImagesIntoChannels(const vector<Mat> & images, vector<Mat> & B, vector<Mat> & G, vector<Mat> & R);

//Mat mergeColorChannels(const Mat & B, const Mat & G, const Mat & R);

float w(int zValue);

// DECLARATIONS: END   //
/////////////////////////



// simple hat function
float w(int zValue)
{
	// Assumption: minimum z value = 0, maximum z value = 255
	return zValue < 128 ? (float)zValue : (float)(255 - zValue);
}

void splitImagesIntoChannels(const vector<Mat> & images, vector<Mat> & B, vector<Mat> & G, vector<Mat> & R)
{
	B.clear();
	G.clear();
	R.clear();
	
	for(int i = 0; i < (int)images.size(); i++)
	{
		Mat singleB, singleG, singleR;
		
		splitImageIntoChannels(images[i], singleB, singleG, singleR);

		B.push_back(singleB);
		G.push_back(singleG);
		R.push_back(singleR);
	}
}

void _recoverSingleChannelCurve
(
	const vector<Mat> & Z,
	float smoothnessLambda, // 20.0f?
	vector<float> & gCurve
)
{
	// number of images
	const int numberOfImages = (int)Z.size();
	
	// number of cols and rows
	const int rows = Z[0].rows;
	const int cols = Z[0].cols;
	
	// number of pixels
	const int numberOfPixels = Z[0].rows * Z[0].cols;
	
	// n? number of possible pixel values
	const int n = 256;
	
	// log delta t; logDelta_t[j] corresponds to B[j] in paper
	vector<int> logDelta_t;
	
	for(int i = 0; i < numberOfImages; i++)
	{
		// set the middle image to have 0 logDelta_t
		logDelta_t.push_back(i - (numberOfImages / 2));
	}
	
	Mat A = Mat(
		numberOfImages * numberOfPixels + n, 	 // rows
		numberOfPixels + n, 					 // cols
		CV_32FC1,								 // type
		0.0f									 // scalar for init
	);
	
	Mat b = Mat(
		numberOfImages * numberOfPixels + n, 	 // rows
		1,										 // cols
		CV_32FC1,								 // type
		0.0f									 // scalar for init
	);
	
	// data fitting equations
	int k = 0; // index to be used for A and b
	int i = 0; // index to be used to indicate the current pixel
	float weight;
	unsigned char Zvalue;
	
	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; col < cols; col++)
		{
			for(int j = 0; j < numberOfImages; j++)
			{
				Zvalue = Z[j].at<unsigned char>(row, col);
				
				weight = w(Zvalue);
				
				A.at<float>(k, Zvalue) = weight;
				
				A.at<float>(k, n + i) = -weight;
				
				b.at<float>(k, 0) = weight * logDelta_t[j];
				
				k++;
			}
			
			i++;
		}
	}
	
	// fix the curve by setting the middle value to 0
	A.at<float>(k, 128) = 1.0f; // it is already 0 in b
	k++;
	
	// include the smoothness equations
	for(int i = 0; i < n; i++)
	{
		weight = w(i);
		
		A.at<float>(k, i) = smoothnessLambda * weight;
		
		A.at<float>(k, i + 1) = -2 * smoothnessLambda * weight;
		
		A.at<float>(k, i + 2) = smoothnessLambda * weight;
		
		k++;
	}
	
	// solve the system using SVD
	Mat solution;
	
	cv::solve(
		A,				// src1
		b,				// src2
		solution,		// dst
		DECOMP_SVD		// flags
	);
	
	// prepare the solution
	gCurve.clear();
	
	for(int i = 0; i < n; i++)
	{
		gCurve.push_back( solution.at<float>(i, 0) );
	}
	
}

Mat createHdrFromBracketedExposureSequence_Debevec
(
	vector<Mat> images,
	//float smoothnessLambda = 1.0f,
	float smoothnessLambda,
	//float resizingFactor = 1.0f
	float resizingFactor
)
{	
	vector<float> Bcurve, Gcurve, Rcurve;
	
	const int numberOfImages = images.size();

	// recover response curves, g curves namely
	recoverResponseCurve(
		images,
		smoothnessLambda, 				// smoothness factor
		resizingFactor, 			// resizing factor
		Bcurve,
		Gcurve,
		Rcurve
	);

	vector<Mat> B, G, R;
	
	// split images into channels
	splitImagesIntoChannels(images, B, G, R);
	
	// log delta t
	vector<int> logDelta_t;
	
	for(int i = 0; i < numberOfImages; i++)
	{
		// set the middle image to have 0 logDelta_t
		logDelta_t.push_back(i - (numberOfImages / 2));
	}
	
	// the things that are recovered are not radience maps but individual color channels
	Mat Bmap = recoverColorChannel(
		Bcurve,
		B,
		logDelta_t
	);
	
	Mat Gmap = recoverColorChannel(
		Gcurve,
		G,
		logDelta_t
	);
	
	Mat Rmap = recoverColorChannel(
		Rcurve,
		R,
		logDelta_t
	);
	

	Mat hdrImage = mergeColorChannels(Bmap, Gmap, Rmap);
	
	return hdrImage;
}


// overloading
void recoverResponseCurve
(
	vector<Mat> & images,
	float smoothnessLambda,
	float resizingFactor,
	vector<float> & B_gCurve,
	vector<float> & G_gCurve,
	vector<float> & R_gCurve
)
{
	vector<Mat> imagesToUse;
	
	// resize if necessary
	if(resizingFactor != 1.0f)
	{
		for(int i = 0; i < (int)images.size(); i++)
		{
			Mat resized;
	
			cv::resize(
				images[i],		// src
				resized,		// dst
				cv::Size(0, 0),	// dsize: compute from fx and fy
				1 / resizingFactor,		// fx
				1 / resizingFactor,		// fy
				cv::INTER_NEAREST // interpolation, may be defined explicity..
			);
		
			imagesToUse.push_back(resized);
		}

	}
	else
	{
		imagesToUse = images;
	}
	
	// split images into channels
	vector<Mat> B, G, R;
	
	splitImagesIntoChannels(imagesToUse, B, G, R);
	
	
	// recover for channel B
	_recoverSingleChannelCurve
	(
		B,
		smoothnessLambda,
		B_gCurve
	);
	
	// recover for channel G
	_recoverSingleChannelCurve
	(
		G,
		smoothnessLambda,
		G_gCurve
	);
	
	// recover for channel R
	_recoverSingleChannelCurve
	(
		R,
		smoothnessLambda,
		R_gCurve
	);
}

Mat recoverColorChannel
(
	const vector<float> & gCurve,
	const vector<Mat> & Z,
	const vector<int> & logDelta_t
)
{
	// number of images
	const int numberOfImages = (int)Z.size();
	
	// number of cols and rows
	const int rows = Z[0].rows;
	const int cols = Z[0].cols;
	
	// number of pixels
	//const int numberOfPixels = Z[0].rows * Z[0].cols;
	
	// total weights, to be used for normalization
	Mat totalWeights(rows, cols, CV_32FC1, 0.0f); // may be used as int?
	
	// weighted sum of irradiences, which is the numerator in Equation 6
	Mat weightedSumOfIrradiences(rows, cols, CV_32FC1, 0.0f);
	
	int weight;
	
	// for all pixel locations y, x
	for(int x = 0; x < cols; x++)
	{
		for(int y = 0; y < rows; y++)
		{
			// for all images image_j
			for(int j = 0; j < numberOfImages; j++)
			{
				const unsigned char & pixelValue = Z[j].at<unsigned char>(y, x);
				
				weight = w(pixelValue);
				
				weightedSumOfIrradiences.at<float>(y, x) += weight * (gCurve[pixelValue] - logDelta_t[j]);
				
				totalWeights.at<float>(y, x) += weight;
			}
		}
	}
	
	Mat & result = weightedSumOfIrradiences;
	
	// normalization
	cv::divide(
		weightedSumOfIrradiences, // src1
		totalWeights, // src2
		result // dst
	);

	// return from log domain
	cv::exp(
		result,
		result
	);
	
	return result;
}














