#include "GestCapturer.h"


GestCapturer::GestCapturer()
{
	galeria = Gallery::Gallery();
	capturer = cv::VideoCapture(0);
	cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);
	getHandsPosition();
	

	/*
	capturer >> frame;
	cv::cvtColor(frame, HSV_frame, cv::COLOR_BGR2HSV);*/

//	for (;;)
//	{
//		capturer >> frame; // get a new frame from camera
//		cvtColor(frame, frame, cv::COLOR_BGR2HSV);
////		GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
//	//	Canny(edges, edges, 0, 30, 3);
//		std::vector<cv::Mat> output;
//		cv::split(frame, output);
//		imshow("Hue", output[0]);
//		imshow("Saturation", output[1]);
//		imshow("Value", output[2]);
//		cv::Mat hue = output[0].clone();
//
//		cv::namedWindow("image");
//
//	//	cv::setMouseCallback("image", this->onMouse, 0);
//		cv::imshow("image", frame);
//		if (cv::waitKey(30) >= 0) break;
//	}
}


GestCapturer::~GestCapturer()
{
	capturer.release();
	cv::destroyWindow("Camera");
	galeria.~Gallery();
}

void GestCapturer::backgroudRemoval()
{
}

void GestCapturer::getHandsPosition()
{
	while(cv::waitKey(30)!=27) {
		capturer >> frame;
		cv::flip(frame, frame, 1);
		cv::rectangle(frame, cv::Rect(0, 0, 200, 200), cv::Scalar(255, 0, 255));
		cv::rectangle(frame, cv::Rect(frame.cols-200, 0, 200, 200), cv::Scalar(255, 255, 255));
		updateCameraView();
	}
}

void GestCapturer::updateCameraView()
{
	cv::imshow("Camera", frame);
}