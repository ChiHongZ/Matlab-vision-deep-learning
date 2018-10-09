// Hough.cpp: 定义控制台应用程序的入口点。
//
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

/** Function Headers */
void Erosion(int, void*);
void Dilation(int, void*);
int main()
{
	Mat srcImage = imread("timg.jpg");
	Mat srcImage0,midImage,dstImage;

	int ksize1 = 5;
	int ksize2 = 5;
	double sigma1 = 10.0;
	double sigma2 = 20.0;
	cv::GaussianBlur(srcImage, srcImage0, cv::Size(ksize1, ksize2), sigma1, sigma2);

	Canny(srcImage0, midImage,100, 200, 3);

  	cvtColor(midImage, dstImage, CV_GRAY2BGR);

	vector<Vec2f> lines;
	
	HoughLines(midImage, lines, 1, CV_PI / 180, 180, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 0), 1, CV_AA);
	}
	
	imshow("原始图像数据", srcImage0);

	imshow("检测直线的效果", dstImage);

	waitKey(0);

	return 0;
}

void Erosion(int, void*)
{
	int erosion_type;
	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	/// 腐蚀操作
	erode(src, erosion_dst, element);
	imshow("Erosion Demo", erosion_dst);
}

/** @function Dilation */
void Dilation(int, void*)
{
	int dilation_type;
	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	///膨胀操作
	dilate(src, dilation_dst, element);
	imshow("Dilation Demo", dilation_dst);
}
