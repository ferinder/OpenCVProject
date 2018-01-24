#include "opencv2/opencv.hpp"
#include "Gallery.h"
#include "GestCapturer.h"
#include <memory>

using namespace cv;

int main(int, char**)
{
	std::shared_ptr<GestCapturer> cap = std::make_shared<GestCapturer>();
	cap->doSomething();
	cap->~GestCapturer();
	return 0;
}