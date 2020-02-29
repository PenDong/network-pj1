#pragma once
#include<iostream>
#include "core/core.hpp" 
#include "highgui/highgui.hpp" 
#include "imgproc/imgproc.hpp" 
#include<opencv.hpp>
using namespace std;
using namespace cv;
class Decode
{
public:
	static void decode();
	static string picture_to_string(Mat& image);
	static int  string_to_ascii(string str);
	static string ascii_to_word(int ascii_number);
	//static bool is_string_valid(string str);
	static bool is_picture_exist(string picture_name);
	static string deal_pixel(uchar*& p, int scare);
	static int count_ascii_value(string str);
	static string path;
	static string project_name;
	//static bool is_picture_exist(string picture_name);
	static bool is_even_number;
	static bool is_start;
	static bool is_end;
};