#pragma once
#include "opencv2\opencv.hpp"

class Gallery
{
private:
	cv::Mat3f picture;
public:
	Gallery();
	~Gallery();

	void changePicture(bool direction);
	void zoomPicture();
	void moveZoomWindow(double xDirection, double yDirection);

private:
	void viewPicture();

};

