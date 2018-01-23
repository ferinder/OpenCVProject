#include "HandTracker.h"


HandTracker::HandTracker()
{
	tracker = cv::TrackerMedianFlow::create();
	Xmove = 0;
	Ymove = 0;
	center.first = 0;
	center.second = 0;
}


HandTracker::~HandTracker()
{
}

void HandTracker::updateTracker(cv::Mat frame)
{
	tracker->update(frame, ROI);
	std::pair<int, int> oldCenter;
	oldCenter.first = center.first;
	oldCenter.second = center.second;
	Xmove = 0;
	Ymove = 0;
	center.first = (ROI.x + ROI.width) / 2;
	center.second = (ROI.y + ROI.height) / 2;
	movement.push_back(std::make_pair<int, int>((oldCenter.first - center.first),
												std::abs(oldCenter.second - center.second)));
	if (movement.size() > 10) { 
		movement.pop_front(); 
	}
	for (auto it = movement.cbegin(); it != movement.cend(); it++) {
		Xmove += (*it).first;
		Ymove += (*it).second;
	}
	std::cout << "X:" << Xmove << "\t Y:" << Ymove << std::endl;
	
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
