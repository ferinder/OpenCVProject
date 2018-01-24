#include "HandTracker.h"


HandTracker::HandTracker()
{
	tracker = cv::TrackerMedianFlow::create();
	Xmove = 0;
	Ymove = 0;
	center.first = 0;
	center.second = 0;
	scale = 0;
	ROIHeight = 0;
}


HandTracker::~HandTracker()
{
}

void HandTracker::updateTracker(cv::Mat frame)
{
	tracker->update(frame, ROI);
	std::pair<int, int> oldCenter;
	int oldROIHeight;
	oldCenter.first = center.first;
	oldCenter.second = center.second;
	oldROIHeight = ROIHeight;
	Xmove = 0;
	Ymove = 0;
	scale = 0;
	center.first = (ROI.x + ROI.width) / 2;
	center.second = (ROI.y + ROI.height) / 2;
	ROIHeight = ROI.height;
	
	movement.push_back(std::make_pair<int, int>(
		center.first - oldCenter.first, center.second - oldCenter.second));
	scaleDeq.push_back(ROIHeight - oldROIHeight);

	if (movement.size() > 10) { 
		movement.pop_front(); 
		scaleDeq.pop_front();
	}
	for (auto it : movement) {
		Xmove += it.first;
		Ymove += it.second;
	}
	for (auto it : scaleDeq)
	{
		scale += it;
	}
	
}

void HandTracker::initTracker(cv::Mat frame, cv::Rect2d roi)
{
	tracker->init(frame, roi);
	ROI = roi;
	ROIHeight = ROI.height;
	center.first = (ROI.x + ROI.width) / 2;
	center.second = (ROI.y + ROI.height) / 2;
}

cv::Rect HandTracker::getROI()
{
	return ROI;
}

int HandTracker::getXmove()
{
	return Xmove;
}

int HandTracker::getYmove()
{
	return Ymove;
}

int HandTracker::getScale()
{
	return scale;
}

void HandTracker::clearMovement()
{
	movement.clear();
	scaleDeq.clear();
}
