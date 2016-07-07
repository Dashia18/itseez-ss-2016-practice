#include "tracking.hpp"

#include <iostream>

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
	std::vector< cv::Point2f > corners;
	int maxCorners = 10;
	double qualityLevel = 0.01;
	double minDistance = 20.;
	
	Mat grey;
	Mat greyConvert;
	cvtColor(frame, grey, CV_BGR2GRAY);
	grey.convertTo(greyConvert, CV_8UC1);
	cv::goodFeaturesToTrack(greyConvert(position_), corners, maxCorners, qualityLevel, minDistance);

	//OpticalFlow
	calcOpticalFlowPyrLK
	






	Rect rectTemp;
	return rectTemp;

}