#include "GestCapturer.h"

typedef cv::Point3_<uint8_t> Pixel;


GestCapturer::GestCapturer()
{
	cv::namedWindow("Camera");
	capturer = cv::VideoCapture(0);
	galeria = std::make_shared<Gallery>();
	tracker = std::make_shared<HandTracker>();
}

GestCapturer::~GestCapturer()
{
	capturer.release();
	cv::destroyWindow("Camera");
}

void GestCapturer::doSomething()
{
	initializeTracker();
	while(!(cv::waitKey(10) >= 0)) {
		capturer >> frame;
		tracker->updateTracker(frame);
		cv::rectangle(frame, tracker->getROI(), cv::Scalar(255, 255, 255));
		updateCameraView();
		int Xmove = tracker->getXmove();
		int Ymove = tracker->getYmove();
		if (Xmove > 10 || Ymove > 10 || Xmove < -10 || Ymove < -10) {
			if (Xmove > 50) {
				galeria->changePicture(true);
				tracker->clearMovement();
			}
			else if (Xmove <- 50) {
				galeria->changePicture(false);
				tracker->clearMovement();
			}
			else {
				galeria->moveZoomWindow(Xmove, Ymove);
			}
		}
		else if (tracker->getScale() >10||tracker->getScale() <-10) {
			galeria->zoomPicture(tracker->getScale() /5);
			tracker->clearMovement();
		}
	}
}

void GestCapturer::initializeTracker() {
	capturer >> frame;
	for (;;) {
		capturer >> frame;
		updateCameraView();
		if (cv::waitKey(30) >= 0) break;
	}
	tracker->initTracker(frame, cv::selectROI(frame));
	cv::Mat object;
	object = frame(tracker->getROI());
	cv::imshow("object", object);
}

void GestCapturer::updateCameraView()
{
	cv::imshow("Camera", frame);	
}
