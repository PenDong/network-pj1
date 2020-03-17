#pragma once
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Video_and_Image
{
private:
	static cv::String image_to_video_source;
	static cv::String image_to_video_des;
	static cv::String video_to_image_source;
	static cv::String video_to_image_des;
public:
	static void video_to_image_fun();
	//static void image_to_vedio_fun();
	static void set_video_to_image_source(string str);
};