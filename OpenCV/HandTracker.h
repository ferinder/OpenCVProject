#pragma once
#include "opencv2\tracking.hpp"
#include"opencv2\core\utility.hpp"
#include <opencv2\highgui\highgui.hpp>
#include <deque>


class HandTracker
{
private:
	cv::Ptr<cv::Tracker> tracker;
	cv::Rect2d ROI;
	std::pair<int, int> center;
	int ROIHeight;
	std::deque<std::pair<int, int>> movement;
	std::deque<int> scaleDeq;
	int Xmove;
	int Ymove;
	int scale;
	
public:
	HandTracker();
	~HandTracker();
	void updateTracker(cv::Mat frame);
	void initTracker(cv::Mat frame, cv::Rect2d roi);
	cv::Rect getROI();
	int getXmove();
	int getYmove();
	int getScale();
	void clearMovement();
};

