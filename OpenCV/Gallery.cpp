#include "Gallery.h"


Gallery::Gallery()
{
	cv::namedWindow("Gallery2", CV_WINDOW_NORMAL);
	initializeFileList();
	printFileList();
	fileListIter = fileList.begin();
	picture = cv::imread(*fileListIter, CV_LOAD_IMAGE_COLOR);
	Gallery::viewPicture();
	//for (;;) if (cv::waitKey(30) >= 27)break;
}

Gallery::~Gallery()
{
	//cv::destroyWindow("Gallery");
}

void Gallery::viewPicture()
{
	cv::imshow("Gallery2", picture);
}

void Gallery::initializeFileList()
{
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	hFind = FindFirstFile(path, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::wstring filePath = std::wstring(path);
			filePath.pop_back(); //kasuje gwiazdkê ze œcie¿ki
			std::wstring fileNameWString = filePath + FindFileData.cFileName;
			std::string fileName(fileNameWString.begin(), fileNameWString.end());
			fileList.push_back(fileName);
		} while (FindNextFile(hFind, &FindFileData));
	}
	FindClose(hFind);
	for (int i = 0; i < 2; i++) //usuwa dwa pierwsze elementy z listy {'.' i '..'}
	{
		if (!fileList.empty() && fileList.front().back() == '.') {
			fileList.erase(fileList.begin());
		}
	}
}

void Gallery::changePicture(bool direction)
{
	if (direction) {
		if (fileListIter != std::prev(fileList.end())) {
			fileListIter = std::next(fileListIter);
		}
		else {
			fileListIter = fileList.begin();
		}
	}
	else {
		if (fileListIter != fileList.begin()) {
			fileListIter = std::prev(fileListIter);
		}
		else {
			fileListIter = std::prev(fileList.end());
		}
	}
	picture = cv::imread(*fileListIter, CV_LOAD_IMAGE_COLOR);
	zoomPic.imgOrginal = picture;
	zoomPic.percent = 1;
	viewPicture();

}

void Gallery::zoomPicture(int percent)
{
	if (percent == 0) return;
	if (percent < 0) percent = 1;

	zoomPic.imgOrginal = cv::imread(*fileListIter, CV_LOAD_IMAGE_COLOR);
	zoomPic.percent = percent;
	zoomPic.xPos = zoomPic.imgOrginal.cols / 2;
	zoomPic.yPos = zoomPic.imgOrginal.rows / 2;
	zoomPic.sizeX = zoomPic.imgOrginal.cols / zoomPic.percent;
	zoomPic.sizeY = zoomPic.imgOrginal.rows / zoomPic.percent;
	updateZoomPic();
}

void Gallery::updateZoomPic() {
	cv::Rect roi(zoomPic.xPos - zoomPic.sizeX / 2,
		zoomPic.yPos - zoomPic.sizeY / 2,
		zoomPic.sizeX, zoomPic.sizeY);
	picture = zoomPic.imgOrginal(roi);
	viewPicture();
}

void Gallery::moveZoomWindow(int xDirection, int yDirection)
{
	if (zoomPic.percent == 1) return;
	if (zoomPic.xPos + xDirection + zoomPic.sizeX / 2 >= zoomPic.imgOrginal.cols ||
		zoomPic.xPos + xDirection - zoomPic.sizeX / 2 < 0 ||
		zoomPic.yPos + yDirection + zoomPic.sizeY / 2 >= zoomPic.imgOrginal.rows ||
		zoomPic.yPos + yDirection - zoomPic.sizeY / 2 < 0) {
		return;
	}
	zoomPic.xPos += xDirection;
	zoomPic.yPos += yDirection;
	updateZoomPic();
}

void Gallery::printFileList()
{
	for (auto it : fileList) {
		std::cout << it << std::endl;
	}
}
