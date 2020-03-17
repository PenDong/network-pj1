#pragma once
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Video_and_Image
{
private:
	static cv::String image_to_video_source;
	static cv::String image_to_video_des;
	//static cv::String video_to_image_source;
	//static cv::String video_to_image_des;
	static int video_length;
public:
	//static void video_to_image_fun();
	static bool image_to_vedio_fun();
	//static void set_video_to_image_source();
	static void set_image_to_video_source(string str);
	static void set_video_length(int l);
	static void set_image_to_video_des(string str);
};