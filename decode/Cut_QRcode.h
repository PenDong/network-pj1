#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>    
#include <opencv2\core\core.hpp>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>


using namespace cv;
using namespace std;

class Cut_QRcode
{
private:
	static string source_path;
	static string source_name;
	static cv::String source_path_and_name;
	static string des_path;
	static string save_proj_name;
	static cv::String save_path_and_name;
	static bool is_find;
	static int save_index;

	static Mat transformCorner(Mat src, RotatedRect rect);
	static Mat transformQRcode(Mat src, RotatedRect rect, double angle);
	// ”√”⁄≈–∂œΩ«µ„
	static bool IsQrPoint(vector<Point>& contour, Mat& img);
	static bool isCorner(Mat& image);
	static double Rate(Mat& count);
	static int leftTopPoint(vector<Point> centerPoint);
	static vector<int> otherTwoPoint(vector<Point> centerPoint, int leftTopPointIndex);
	static double rotateAngle(Point leftTopPoint, Point rightTopPoint, Point leftBottomPoint);
	static bool is_picture_exist(string picture_name);
	static void cut_each_qrcode();
public:
	static void cut_qrcodes();
};