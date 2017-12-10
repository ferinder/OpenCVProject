#include "Gallery.h"



Gallery::Gallery()
{
	cv::namedWindow("Gallery", CV_WINDOW_NORMAL);
	fileList = Gallery::getFileList();
	fileListIter = fileList.begin();
	Gallery::updatePicture();
}


Gallery::~Gallery()
{
	cv::destroyWindow("Gallery");
}

void Gallery::updatePicture()
{
	picture = cv::imread(*fileListIter, CV_LOAD_IMAGE_COLOR);
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
		if (fileListIter != std::prev(fileList.end())) {
			fileListIter = std::next(fileListIter);
		}
		else {
			fileListIter = fileList.begin();
		}
	}
	else {
		if (fileListIter != fileList.begin())	{
			fileListIter = std::prev(fileListIter);
		}
		else {
			fileListIter = std::prev(fileList.end());
		}
	}
	Gallery::updatePicture();
}

void Gallery::zoomPicture()
{
}

void Gallery::moveZoomWindow(double xDirection, double yDirection)
{
}
