#include "Gallery.h"



Gallery::Gallery()
{
	cv::namedWindow("Gallery", CV_WINDOW_NORMAL);
	this->fileList = this->getFileList();
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
	cv::imshow("Gallery", picture);
}

std::vector<std::string> Gallery::getFileList()
{
	std::vector<std::string> m_file_list;
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	hFind = FindFirstFile(path, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::wstring filePath = std::wstring(path);
			filePath.pop_back();
			std::wstring fileNameWString = filePath + FindFileData.cFileName;
			std::string fileName(fileNameWString.begin(), fileNameWString.end());
			m_file_list.push_back(fileName);
		} while (FindNextFile(hFind, &FindFileData));
	}
	FindClose(hFind);
	for (int i = 0; i < 2; i++)
	{
		if (!m_file_list.empty() &&
			(m_file_list.front().back() == '.')) {
			m_file_list.erase(m_file_list.begin());
		}
	}
	return m_file_list;
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
		if (this->fileListIter != this->fileList.begin())	{
			this->fileListIter = std::prev(this->fileListIter);
		}
		else {
			this->fileListIter = std::prev(this->fileList.end());
		}
	}
	this->picture = cv::imread(*this->fileListIter, CV_LOAD_IMAGE_COLOR);
	this->viewPicture();
}

void Gallery::zoomPicture()
{
}

void Gallery::moveZoomWindow(double xDirection, double yDirection)
{
}

void Gallery::printFileList()
{
	for (auto it : this->fileList) {
		std::cout << it << std::endl;
	}
}
