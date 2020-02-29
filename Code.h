#pragma once
#include<iostream>
#include "core/core.hpp" 
#include "highgui/highgui.hpp" 
#include "imgproc/imgproc.hpp" 
#include<opencv.hpp>
using namespace std;
using namespace cv;

class Code
{
public:
	static string obj_name;
	static string path;
	static void code();
	static void draw_0(Mat& image, int index);
	static void draw_1(Mat& image, int index);
	static void draw_pictures(char c,int index,bool is_head,bool is_end);
	static string ascii_to_binary(char c);
	static string to_string(int number);
};