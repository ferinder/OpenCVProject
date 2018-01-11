#include "HandTracker.h"


HandTracker::HandTracker()
{
	tracker = cv::TrackerMedianFlow::create();
}


HandTracker::~HandTracker()
{
}

void HandTracker::updateTracker(cv::Mat frame)
{
	tracker->update(frame, ROI);
	center.first = (ROI.x + ROI.width) / 2;
	center.second = (ROI.y + ROI.height) / 2;
}

void HandTracker::initTracker(cv::Mat frame, cv::Rect2d roi)
{
	tracker->init(frame, roi);
	std::cout << "tutaj jestem";
	ROI = roi;
}

cv::Rect HandTracker::getROI()
{
	return ROI;
}
