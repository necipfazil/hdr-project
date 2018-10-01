/** METU CENG587 Project
  * Author: Necip Fazil Yildiran
  * */

#ifndef __DEBEVEC_RECOVERY_H__
#define __DEBEVEC_RECOVERY_H__

#include<vector>
#include<opencv2/core.hpp>

cv::Mat createHdrFromBracketedExposureSequence_Debevec
(
	std::vector<cv::Mat> images,
	float smoothnessLambda = 1.0f,
	float resizingFactor = 1.0f
);

#endif
