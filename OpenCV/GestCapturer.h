#pragma once
#include "opencv2\opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <algorithm>

#include "Gallery.h"
#include "HandTracker.h"

struct Hand {
	int pos_X;
	int pos_Y;
	int finger_count;
	int starting_pos_X;
	int starting_pos_Y;
	int hue;
	std::vector<int> hueHist;
	cv::Mat img;
};

class GestCapturer
{
private:
	Gallery galeria;
	cv::Mat frame;
	cv::VideoCapture capturer;
	Hand hand;
	HandTracker tracker;
public:
	GestCapturer();
	~GestCapturer();

private:
	void backgroudRemoval();
	void getHandPosition();
	void updateCameraView();
	void setHandHue(cv::Mat ROI);
};


