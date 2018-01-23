#pragma once
#include "opencv2\opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>

#include "Gallery.h"
#include "HandTracker.h"

class GestCapturer
{
private:
	std::shared_ptr<Gallery> galeria;
	std::shared_ptr<HandTracker> tracker;
	cv::Mat frame;
	cv::VideoCapture capturer;
public:
	GestCapturer();
	~GestCapturer();
	void doSomething();
private:
	void updateCameraView();
	void initializeTracker();

};
