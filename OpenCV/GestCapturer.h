#pragma once
#include "opencv2\opencv.hpp"

#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>

#include <vector>
#include <string>
#include "Gallery.h"

class GestCapturer
{
private:
	Gallery galeria;
	cv::Mat frame;
	cv::Mat HSV_frame;
	cv::Mat background;
	cv::VideoCapture capturer;
public:
	GestCapturer();
	~GestCapturer();

private:
	void backgroudRemoval();
	void getHandsPosition();
	void updateCameraView();
};


