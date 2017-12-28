#include "opencv2/opencv.hpp"
#include "Gallery.h"
#include "GestCapturer.h"
using namespace cv;

int main(int, char**)
{
	GestCapturer cap = GestCapturer::GestCapturer();
	
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
//	 the camera will be deinitialized automatically in VideoCapture destructor
	//Gallery galeria = Gallery::Gallery();
	//galeria.printFileList();
	//int keyPressed;
	//do {
	//	keyPressed = cv::waitKey(0);
	//	if (keyPressed == 108) {
	//		//l - lewo
	//		galeria.changePicture(false);
	//	}
	//	else if (keyPressed == 112) {
	//		//p - prawo
	//		galeria.changePicture(true);
	//	}
	//	else if (keyPressed == 122) {
	//		//z -przybliz
	//		galeria.zoomPicture(2);
	//	}
	//	else if (keyPressed == 121) {
	//		//y - przybliz bardziej ;d
	//		galeria.zoomPicture(4);
	//	}
	//	else if (keyPressed == 119) {
	//		//w - przesuñ w górê
	//		galeria.moveZoomWindow(0, -50);
	//	}
	//	else if (keyPressed == 115) {
	//		//s - przesuñ w dó³
	//		galeria.moveZoomWindow(0, 50);
	//	}
	//	else if (keyPressed == 100) {
	//		// d - przesuñ w prawo
	//		galeria.moveZoomWindow(50, 0);
	//	}
	//	else if (keyPressed == 97) {
	//		//a - przesuñ w lewo
	//		galeria.moveZoomWindow(-50, 0);
	//	}
	//} while (keyPressed != 27);
	return 0;
}