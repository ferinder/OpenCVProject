#include "opencv2/opencv.hpp"
#include "Gallery.h"
//using namespace cv;

int main(int, char**)
{
	//VideoCapture cap(0); // open the default camera
	//if (!cap.isOpened())  // check if we succeeded
	//	return -1;

	//Mat edges;
	//namedWindow("edges", 1);
	//for (;;)
	//{
	//	Mat frame;
	//	cap >> frame; // get a new frame from camera
	//	cvtColor(frame, edges, COLOR_BGR2GRAY);
	//	GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
	//	Canny(edges, edges, 0, 30, 3);
	//	imshow("edges", edges);
	//	if (waitKey(30) >= 0) break;
	//}
	// the camera will be deinitialized automatically in VideoCapture destructor
	Gallery galeria = Gallery::Gallery();
	for (auto it : galeria.fileList) {
		std::cout << it << std::endl;
	}
	int keyPressed;
	do {
		keyPressed = cv::waitKey(0);
		if (keyPressed == 108) {
			//l - lewo
			galeria.changePicture(false);
		}
		else if (keyPressed == 112)
		{ //p - prawo
			galeria.changePicture(true);
		}
	} while (keyPressed != 27);
	return 0;
}