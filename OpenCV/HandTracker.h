#pragma once
#include "opencv2\tracking.hpp"
#include"opencv2\core\utility.hpp"
#include <opencv2\highgui\highgui.hpp>


class HandTracker
{
private:
	cv::Ptr<cv::Tracker> tracker;
	cv::Rect2d ROI;
	std::pair<int, int> center;
	
public:
	HandTracker();
	~HandTracker();
	void updateTracker(cv::Mat frame);
	void initTracker(cv::Mat frame, cv::Rect2d roi);
	cv::Rect getROI();
};

