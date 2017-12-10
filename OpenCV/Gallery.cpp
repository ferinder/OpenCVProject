#include "Gallery.h"


Gallery::Gallery()
{
	cv::namedWindow("Gallery", CV_WINDOW_NORMAL);
	this->initializeFileList();
	this->fileListIter = this->fileList.begin();
	this->picture = cv::imread(*fileListIter, CV_LOAD_IMAGE_COLOR);
	Gallery::viewPicture();
}

Gallery::~Gallery()
{
	cv::destroyWindow("Gallery");
}

void Gallery::viewPicture()
{
	cv::imshow("Gallery", this->picture);
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
			this->fileList.push_back(fileName);
		} while (FindNextFile(hFind, &FindFileData));
	}
	FindClose(hFind);
	for (int i = 0; i < 2; i++) //usuwa dwa pierwsze elementy z listy {'.' i '..'}
	{
		if (!this->fileList.empty() && this->fileList.front().back() == '.') {
			this->fileList.erase(this->fileList.begin());
		}
	}
}

void Gallery::changePicture(bool direction)
{
	if (direction) {
		if (this->fileListIter != std::prev(this->fileList.end())) {
			this->fileListIter = std::next(this->fileListIter);
		}
		else {
			this->fileListIter = this->fileList.begin();
		}
	}
	else {
		if (this->fileListIter != this->fileList.begin()) {
			this->fileListIter = std::prev(this->fileListIter);
		}
		else {
			this->fileListIter = std::prev(this->fileList.end());
		}
	}
	this->picture = cv::imread(*this->fileListIter, CV_LOAD_IMAGE_COLOR);
	this->viewPicture();
}

void Gallery::zoomPicture(int percent)
{
	this->zoomPic.imgOrginal = cv::imread(*this->fileListIter, CV_LOAD_IMAGE_COLOR);
	this->zoomPic.percent = percent;
	this->zoomPic.xPos = this->zoomPic.imgOrginal.cols / 2;
	this->zoomPic.yPos = this->zoomPic.imgOrginal.rows / 2;
	this->zoomPic.sizeX = this->zoomPic.imgOrginal.cols / this->zoomPic.percent;
	this->zoomPic.sizeY = this->zoomPic.imgOrginal.rows / this->zoomPic.percent;
	this->updateZoomPic();
}

void Gallery::updateZoomPic() {
	cv::Rect roi(this->zoomPic.xPos - this->zoomPic.sizeX / 2,
		this->zoomPic.yPos - this->zoomPic.sizeY / 2,
		this->zoomPic.sizeX, this->zoomPic.sizeY);
	this->picture = this->zoomPic.imgOrginal(roi);
	this->viewPicture();
}

void Gallery::moveZoomWindow(int xDirection, int yDirection)
{
	if (this->zoomPic.xPos + xDirection + this->zoomPic.sizeX / 2 >= this->zoomPic.imgOrginal.cols ||
		this->zoomPic.xPos + xDirection - this->zoomPic.sizeX / 2 < 0 ||
		this->zoomPic.yPos + yDirection + this->zoomPic.sizeY / 2 >= this->zoomPic.imgOrginal.rows ||
		this->zoomPic.yPos + yDirection - this->zoomPic.sizeY / 2 < 0) {
		return;
	}
	this->zoomPic.xPos += xDirection;
	this->zoomPic.yPos += yDirection;
	this->updateZoomPic();
}

void Gallery::printFileList()
{
	for (auto it : this->fileList) {
		std::cout << it << std::endl;
	}
}
