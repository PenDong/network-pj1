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

class Decode
{
private:
	static enum COLORS { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };
	static int pos_x;
	static int pos_y;

	static int upflag0, upflag1, upflag2;
	static int downflag0, downflag1, downflag2;
	static int leftflag0, leftflag1, leftflag2;
	static int rightflag0, rightflag1, rightflag2;
	static double left_rate;
	static double right_rate;
	static double up_rate;
	static double down_rate;
	static int correct_row;
	static int correct_col;
	//这是一条分割线
	static int temp_left;
	static int temp_right;
	static int temp_up;
	static int temp_down;
	static int row_scale;
	static int col_scale;


	static string image_path;
	static string proj_name;
	static cv::String image_path_and_name;
	static string out_file_path_and_name;

	static bool is_start;
	static bool is_end;
	static int now_image;
	static bool is_good;

	static char buffer[119];
	static int buffer_index;


	static int get_leftflag(Mat& image, int pos);
	static int get_rightflag(Mat& image, int pos);
	static int get_upflag(Mat& image, int pos);
	static int get_downtflag(Mat& image, int pos);
	static double get_left_and_up_rate(int x0, int x1, int x2);
	static double get_right_and_down_rate(int x0, int x1, int x2);
	static void initiate_image(Mat& image);
	static void change_pos();
	static COLORS int_to_color(int number);
	static COLORS further_judge_color(int p0_infor, int p1_infor, int p2_infor);
	static COLORS get_color(Mat& image, int temp_pos_x, int temp_pos_y);
	static int color_to_int(COLORS color);
	static string ascii_to_binary(int c);
	static bool read_and_write_information(Mat& image);
	static void write_into_txt_file();


public:
	static void decode();
	static void set_out_file_path_and_name(string str);
};