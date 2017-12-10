#pragma once
#include "opencv2\opencv.hpp"
#include <string>
#include <vector>
#include <Windows.h>
#include <filesystem>

class Gallery
{
public:
	cv::Mat picture;
	std::vector<std::string> fileList;
	std::vector<std::string>::iterator fileListIter;
	wchar_t* path = L"C:\\Users\\Szefu\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\OpenCV\\Pictures\\*";
public:
	Gallery();
	~Gallery();
	void changePicture(bool direction);
	void zoomPicture();
	void moveZoomWindow(double xDirection, double yDirection);
public:
	void viewPicture();
	std::vector<std::string> getFileList();
};
//
//class FileListIterator
//{
//public:
//	FileListIterator();
//	~FileListIterator();
//
//};