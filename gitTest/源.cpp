#include <opencv2\opencv.hpp> 
#include <opencv2\tracking\tracking.hpp>
using namespace cv;
int main() {
	cv::VideoCapture capture; capture.open("xcdh.mp4");
	//����tracker
	Ptr<Tracker> tracker = TrackerMIL::create();
	//ROIѡȡģ��
	Rect2d roi;
	Mat frame;
	capture >> frame;
	roi = selectROI("tracker", frame);
	//���û��ѡ��ROI������
	if (roi.width == 0 || roi.height == 0)
		return 0;
	// ��ʼ��tracker
	tracker->init(frame, roi); int cnt = 0;
	while (true) {
		capture >> frame;
		// ��ȡʧ����������
		if (frame.empty())break;
		// update
		tracker->update(frame, roi);
		// �軭���
		rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
		// ��ʾ
		imshow("frame", frame); cnt++;
		// �� ESC ���˳�
		if (waitKey(1) == 25)break;
	}
	return 0;