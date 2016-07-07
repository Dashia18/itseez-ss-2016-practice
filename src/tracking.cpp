#include "tracking.hpp"

#include <iostream>
#include <vector>

using std::string;
using std::shared_ptr;
using namespace cv;

shared_ptr<Tracker> Tracker::CreateTracker(const string &name) {
  std::cerr << "Failed to create tracker with name '" << name << "'"
            << std::endl;
  if (name == "median_flow") {
	  return std::make_shared<MedianFlowTracker>();
  }
  return nullptr;
}

bool MedianFlowTracker::Init(const cv::Mat &frame, const cv::Rect &roi) {
	if (!frame.empty()) {
		frame.copyTo(frame_);
		position_ = Rect(roi.x, roi.y, roi.width, roi.height);
		return true;
	}
	else
	{
		return false;
	}
}
cv::Rect MedianFlowTracker::Track(const cv::Mat &frame) {

	//Features
	std::vector< cv::Point2f > cornersOld;
	int maxCorners = 10;
	double qualityLevel = 0.01;
	double minDistance = 20.;
	
	Mat greyOld;
	Mat greyOldConvert;
	cvtColor(frame_, greyOld, CV_BGR2GRAY);
	greyOld.convertTo(greyOldConvert, CV_8UC1);
	cv::goodFeaturesToTrack(greyOldConvert(position_), cornersOld, maxCorners, qualityLevel, minDistance);

	//recalc coordinade + position_ (x, y) - roi area
	for (int ind = 0; ind < cornersOld.size(); ind++) {
		cornersOld[ind].x = cornersOld[ind].x + position_.x;
		cornersOld[ind].y = cornersOld[ind].y + position_.y;
	}

	//OpticalFlow
	Mat greyNew;
	Mat greyNewConvert;
	cv::Mat frameCopy;
	frame.copyTo(frameCopy);
	cvtColor(frameCopy, greyNew, CV_BGR2GRAY);
	greyNew.convertTo(greyNewConvert, CV_8UC1);
	
	if (!cornersOld.empty())
	{
		std::vector< cv::Point2f > cornersNew;
		std::vector <uchar> status;
		std::vector <float> err;
		cv::calcOpticalFlowPyrLK(greyOldConvert, greyNewConvert, cornersOld, cornersNew, status, err);

		int indWithOutBad = 0;
		for (int indCornerNew = 0; indCornerNew < cornersNew.size(); indCornerNew++)
		{	
			if (!status[indCornerNew] == 0) {
				cornersNew[indWithOutBad++] = cornersNew[indCornerNew];                                      
			}
		}
		cornersNew.resize(indWithOutBad);
	}
	
	//median shift tbd





	Rect rectTemp;
	return rectTemp;

}