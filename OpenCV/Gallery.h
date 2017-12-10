#pragma once
#include "opencv2\opencv.hpp"
#include <string>
#include <vector>
#include <Windows.h>

struct Zoom {
	cv::Mat imgOrginal;
	int percent;
	int xPos;
	int yPos;
	int sizeX;
	int sizeY;
};

class Gallery
{
private:
	Zoom zoomPic;
	cv::Mat picture;
	std::vector<std::string> fileList;
	std::vector<std::string>::iterator fileListIter;
	wchar_t* path = L"C:\\Users\\Szefu\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\OpenCV\\Pictures\\*";
public:
	Gallery();
	~Gallery();
	void changePicture(bool direction);
	void zoomPicture(int percent);
	void moveZoomWindow(int xDirection, int yDirection);
	void printFileList();
private:
	void viewPicture();
	void initializeFileList();
	void updateZoomPic();
};