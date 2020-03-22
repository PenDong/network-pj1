#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<cmath>
#include<time.h>
#include<stack>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define SCALE 28

class Create_images
{
private:
	static enum COLORS { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };
	static int pos_x;
	static int pos_y;
	static string doc_path;
	static string image_save_path;
	static string project_name;
	static int number_of_image;
	static cv::String cv_path;
	static Mat image;
	static int sum0, sum1, sum2;
	//static int number_of_images;

	static void get_color_pixel(uchar*& p, COLORS color);
	static COLORS number_to_color(int number);
	static void draw_block(int x, int y, int scale, COLORS color);
	static void draw_big_block(int x, int y, int scale);
	static void draw_dingwei();
	static void draw_edge();
	static void initiate_new_image();
	static void change_pos();
	static string ascii_to_binary(int c);
	static void write_each(int c);
	static void write_Colorful_QRcode();
	static void write_check();
	static void draw_start();
	static void draw_end();

	//对外接口
public:
	static void create_imgaes();
	static void set_doc_path(string str);
	static int get_number_of_imgae();

};