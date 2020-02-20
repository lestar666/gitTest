#include <opencv2\opencv.hpp> 
#include <opencv2\tracking\tracking.hpp>
using namespace cv;
int main() {
	cv::VideoCapture capture; capture.open("xcdh.mp4");
	//创建tracker
	Ptr<Tracker> tracker = TrackerMIL::create();
	//ROI选取模版
	Rect2d roi;
	Mat frame;
	capture >> frame;
	roi = selectROI("tracker", frame);
	//如果没有选择ROI则跳出
	if (roi.width == 0 || roi.height == 0)
		return 0;
	// 初始化tracker
	tracker->init(frame, roi); int cnt = 0;
	while (true) {
		capture >> frame;
		// 读取失败跳出程序
		if (frame.empty())break;
		// update
		tracker->update(frame, roi);
		// 描画结果
		rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
		// 显示
		imshow("frame", frame); cnt++;
		// 按 ESC 键退出
		if (waitKey(1) == 25)break;
	}
	return 0;