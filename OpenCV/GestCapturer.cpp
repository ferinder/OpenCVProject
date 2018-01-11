#include "GestCapturer.h"

typedef cv::Point3_<uint8_t> Pixel;


GestCapturer::GestCapturer()
{
	cv::namedWindow("Camera");
	capturer = cv::VideoCapture(0);
	galeria = Gallery();
	tracker = HandTracker();
	capturer >> frame;
	for (;;) {
		capturer >> frame; 
		cv::imshow("Camera", frame);
		if (cv::waitKey(30) >= 0) break;
	}
	tracker.initTracker(frame, cv::selectROI(frame));
	while(!(cv::waitKey(10) >= 0)) {
		capturer >> frame;
		tracker.updateTracker(frame);
		cv::rectangle(frame, tracker.getROI(), cv::Scalar(255, 255, 255));
		cv::Mat frame2;
		cv::flip(frame, frame2, 1);
		cv::imshow("Camera", frame2);
		
	}
}


GestCapturer::~GestCapturer()
{
	capturer.release();
	cv::destroyWindow("Camera");
}

void GestCapturer::backgroudRemoval()
{
}

void GestCapturer::getHandPosition()
{
	cv::Mat ROI;
	while(cv::waitKey(30)!=27) {
		capturer >> frame;
		cv::flip(frame, frame, 1);
		cv::rectangle(frame, cv::Rect(frame.cols - 200, 0, 200, 250), cv::Scalar(255, 0, 0));
		cv::drawMarker(frame, cv::Point(frame.cols - 100, 125), cv::Scalar(255, 255, 255), 
			cv::MARKER_CROSS, 20, 2);
		cv::rectangle(frame, cv::Rect(frame.cols - 140, 80, 80, 80), cv::Scalar(255, 255, 255));
		ROI = frame(cv::Rect(frame.cols - 140, 80, 80, 80));
		updateCameraView();
	}
	setHandHue(ROI);
}

void GestCapturer::updateCameraView()
{
	cv::imshow("Camera", frame);	
}


void GestCapturer::setHandHue(cv::Mat ROI)
{
	hand.img = ROI.clone();
	cv::imwrite("../Ziemniaki.jpg", hand.img);
	//hand.img = cv::imread("../HAND.jpg");
	cv::cvtColor(hand.img, hand.img, cv::COLOR_BGR2HSV);

	hand.img.forEach<Pixel>([&](Pixel& pixel, const int *pos) -> void {
		if (pixel.x < 15) return;
		hand.hueHist[pixel.x] += 1;
	});
	for (auto it = hand.hueHist.cbegin(); it != hand.hueHist.cend(); ++it) std::cout << std::distance(hand.hueHist.cbegin(), it) << "-" << *it << std::endl;
	hand.hue = std::distance(hand.hueHist.begin(),
		std::max_element(hand.hueHist.begin(), hand.hueHist.end()));
	std::cout << hand.hue <<"::" << *std::max_element(hand.hueHist.begin(), 
		hand.hueHist.end()) << std::endl;
	
}
	//cv::namedWindow("roi");

	//cv::cvtColor(ROI, ROI, cv::COLOR_BGR2HSV);
	//std::vector<cv::Mat> output;
	//cv::split(ROI, output);

//	cv::imshow("roi", output[0]);
	//if (cv::waitKey(30) == 27) cv::imwrite("../HAND.jpg", ROI);

// ca³a d³oñ - zgarnij pozycjê i zacznij œledziæ
// jeden palec + przesuniêcie - przesuniêcie przybli¿onego obszaru
// dwa palce + przesuniêcie - zoom
// trzy palce + przesuniêcie - obrót
// cztery palce + przesuniêcie - zmiana zdjêcia