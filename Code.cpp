#include<iostream>
#include "core/core.hpp" 
#include "highgui/highgui.hpp" 
#include "imgproc/imgproc.hpp" 
#include<opencv.hpp>
#include"Code.h"
#include<stack>
using namespace std;
using namespace cv;

void Code::draw_0(Mat& image, int index)
{
	for (int i = 200; i < 400; i++)
	{
		uchar* p = image.ptr<uchar>(i);
		for (int j = 100 + index * 15; j < 100 + index * 15 + 5; j++)
		{
			p[j] = 0;
		}
	}
}
void Code::draw_1(Mat& image, int index)
{
	for (int i = 200; i < 400; i++)
	{
		uchar* p = image.ptr<uchar>(i);
		for (int j = 100 + index * 15; j < 100 + index * 15 + 10; j++)
		{
			p[j] = 0;
		}
	}
}

string Code::ascii_to_binary(char c)
{
	string binary_str="";
	int number = (int)c;
	//cout << number << endl;
	stack<int> stk;
	while (number)
	{
		int temp = number % 2;
		stk.push(temp);
		number /= 2;
	}
	while (!stk.empty())
	{
		int temp = stk.top();
		stk.pop();
		if (temp)
			binary_str += "1";
		else
			binary_str += "0";
	}
	int add_0_times = 8 - binary_str.length();
	for (int i = add_0_times; i >= 1; i--)
		binary_str = "0"+binary_str;
	//cout << "二进制码为：" << binary_str << endl;
	return binary_str;

}

string Code::to_string(int number)
{
	if (number == 0)
		return "0";
	string str="";
	char c;
	stack<char> stk;
	while (number)
	{
		int temp = number % 10;
		c = (char)(temp + 48);
		stk.push(c);
		number /= 10;
	}
	while (!stk.empty())
	{
		c = stk.top();
		stk.pop();
		str += c;
	}
	return str;
	//cout << "flag" << endl;
}
void Code::draw_pictures(char c, int index, bool is_head = false, bool is_end = false)
{
	string infor = "";

	string head_str = "0";
	if (index % 2)
		head_str += "1";
	else
		head_str += "0";


	if (is_head)
	{
		infor = "00000000";
	}
	else if (is_end)
	{
		infor = "11111111";
	}
	else
	{
		infor = ascii_to_binary(c);
	}
	infor = head_str + infor;
	
	Mat image(600, 600, CV_8UC1);

	for (int i = 0; i < image.rows; i++)
	{
		uchar* p = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols; j++)
		{
			p[j] = 255;
		}
	}
	for (int i = 0; i < infor.length(); i++)
	{
		if (infor[i] == '1')
			draw_1(image, i);
		else if (infor[i] == '0')
			draw_0(image, i);
	}
	cv::String cv_save = path + obj_name + to_string(index)+".jpg";
	cout << cv_save << endl;
	imwrite(cv_save, image);
	cout << "保存成功,字符【" << c << "】" << "被保存为:   " << infor << "    " << "保存文件名" << cv_save << endl;
}
void Code::code()
{
	cout << "请输入项目名:" << endl;
	cin >> Code::obj_name;
	cout << "请输入生成文件储存地址:(末尾+【/】)" << endl;
	cin >> Code::path;
	cout << "请输编码的内容:" << endl;
	string infor;
	cin >> infor;
	draw_pictures(' ', 0, true, false);
	for (int i = 0; i < infor.length(); i++)
	{
		draw_pictures(infor[i], i + 1);
	}
	draw_pictures(' ', infor.length() + 1, false, true);
}


string Code::obj_name;
string Code::path;