#include <opencv2/opencv.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

#include "kdtree.h"

class PointT : public std::array<double, 2>
{
public:
	static const int DIM = 2;

	PointT() {}
	PointT(double x, double y)
	{ 
		(*this)[0] = x;
		(*this)[1] = y;
	}

	operator cv::Point2d() const { return cv::Point2d((*this)[0], (*this)[1]); }
};

int main(int argc, char **argv)
{
	const int width = 500;
	const int height = 500;
	cv::Mat img = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

	const int npoints = 300;
	std::vector<PointT> points(npoints);
	for (int i = 0; i < npoints; i++)
	{
		const int x = rand() % width;
		const int y = rand() % height;
		points[i] = PointT(x, y);
	}

	for (const auto& pt : points)
		cv::circle(img, cv::Point2d(pt), 1, cv::Scalar(0, 255, 255), -1);

	kdt::KDTree<PointT> kdtree(points);
	const PointT query(0.5 * width, 0.5 * height);
	cv::circle(img, cv::Point2d(query), 1, cv::Scalar(0, 0, 255), -1);

	// nearest neigbor search
#if 0 
	const int idx = kdtree.nnSearch(query);
	cv::circle(img, cv::Point2d(points[idx]), 1, cv::Scalar(255, 255, 0), -1);
#endif

	// k-nearest neigbors search
#if 0
	const int k = 10;
	const std::vector<int> indices = kdtree.knnSearch(query, k);
	for (int i : indices)
		cv::circle(img, cv::Point2d(points[i]), 1, cv::Scalar(255, 255, 0), -1);
#endif

	// radius search
#if 1
	const double radius = 50;
	const std::vector<int> indices = kdtree.radiusSearch(query, radius);
	for (int i : indices)
		cv::circle(img, cv::Point2d(points[i]), 1, cv::Scalar(255, 255, 0), -1);
	cv::circle(img, cv::Point2d(query), cvRound(radius), cv::Scalar(0, 0, 255));
#endif

	cv::imshow("result", img);
	cv::waitKey(0);

	return 0;
}