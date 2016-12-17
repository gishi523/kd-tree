#include <opencv2/opencv.hpp>
#include <iostream>
#include <array>
#include <vector>

#include "kdtree.h"

// user-defined point type
// inherits std::array in order to use operator[]
class MyPoint : public std::array<double, 2>
{
public:

	// dimension of space (or "k" of k-d tree)
	// KDTree class accesses this member
	static const int DIM = 2;

	// the constructors
	MyPoint() {}
	MyPoint(double x, double y)
	{ 
		(*this)[0] = x;
		(*this)[1] = y;
	}

	// conversion to OpenCV Point2d
	operator cv::Point2d() const { return cv::Point2d((*this)[0], (*this)[1]); }
};

int main(int argc, char **argv)
{
	const int seed = argc > 1 ? std::stoi(argv[1]) : 0;
	srand(seed);

	// generate space
	const int width = 500;
	const int height = 500;
	cv::Mat img = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

	// generate points
	const int npoints = 100;
	std::vector<MyPoint> points(npoints);
	for (int i = 0; i < npoints; i++)
	{
		const int x = rand() % width;
		const int y = rand() % height;
		points[i] = MyPoint(x, y);
	}

	for (const auto& pt : points)
		cv::circle(img, cv::Point2d(pt), 1, cv::Scalar(0, 255, 255), -1);

	// build k-d tree
	kdt::KDTree<MyPoint> kdtree(points);

	// generate query (center of the space)
	const MyPoint query(0.5 * width, 0.5 * height);
	cv::circle(img, cv::Point2d(query), 1, cv::Scalar(0, 0, 255), -1);

	// nearest neigbor search
	const cv::Mat I0 = img.clone();
	const int idx = kdtree.nnSearch(query);
	cv::circle(I0, cv::Point2d(points[idx]), 1, cv::Scalar(255, 255, 0), -1);
	cv::line(I0, cv::Point2d(query), cv::Point2d(points[idx]), cv::Scalar(0, 0, 255));

	// k-nearest neigbors search
	const cv::Mat I1 = img.clone();
	const int k = 10;
	const std::vector<int> knnIndices = kdtree.knnSearch(query, k);
	for (int i : knnIndices)
	{
		cv::circle(I1, cv::Point2d(points[i]), 1, cv::Scalar(255, 255, 0), -1);
		cv::line(I1, cv::Point2d(query), cv::Point2d(points[i]), cv::Scalar(0, 0, 255));
	}
	
	// radius search
	const cv::Mat I2 = img.clone();
	const double radius = 50;
	const std::vector<int> radIndices = kdtree.radiusSearch(query, radius);
	for (int i : radIndices)
		cv::circle(I2, cv::Point2d(points[i]), 1, cv::Scalar(255, 255, 0), -1);
	cv::circle(I2, cv::Point2d(query), cvRound(radius), cv::Scalar(0, 0, 255));

	// show results
	cv::imshow("Nearest neigbor search", I0);
	cv::imshow("K-nearest neigbors search (k = 10)", I1);
	cv::imshow("Radius search (radius = 50)", I2);

	cv::waitKey(0);

	return 0;
}