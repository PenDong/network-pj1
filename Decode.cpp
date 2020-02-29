#include<iostream>
#include "core/core.hpp" 
#include "highgui/highgui.hpp" 
#include "imgproc/imgproc.hpp" 
#include<opencv.hpp>
#include"Decode.h"
#include"Code.h"
#include<fstream>
using namespace std;
using namespace cv;
void Decode::decode()
{
	Mat image;
	string result_str="";
	cout << "请输入文件地址:(后面加上【\\】)"<<endl;
	cin >> path;
	cv::String cv_path = path;//要加载图片必须路径字符串必须是cv::String
	cout << "请输入项目名:" << endl;
	cin >> project_name;
	for(int i=0; ;i++)
	{
		string temp_path = path +project_name+ Code::to_string(i) + ".jpg";
		if (!is_picture_exist(temp_path))
			break;
		cv_path = temp_path;
		cout << "正在对" << cv_path << "进行操作" << endl;
		image = imread(cv_path);
		result_str += ascii_to_word(string_to_ascii(picture_to_string(image)));
	}
	cout << "解码得到结果为：" << endl;
	cout << result_str;
	if (!is_end)
		cout << "没有度到结束位，可能存在异常"<<endl;
	
}
//判断文件是否存在
bool Decode::is_picture_exist(string picture_name)
{
	ifstream f(picture_name.c_str());
	return f.good();
}
//对像素点进行算法分析
string Decode::deal_pixel(uchar*& p, int scare)
{
	string information = "";
	int number_of_information = 0;
	int zero_lenth;
	int temp_count = 0;
	bool is_count = true;
	for (int i = 0; i < scare; i++)
	{
		if (p[i] <= 100)
		{
			temp_count += 1;
			is_count = true;
		}
		else
		{
			if (i + 3 < scare)
			{
				if ((p[i + 1] <= 80 || p[i + 2] <= 80 || p[i + 3] <= 80))//80  100
				{
					temp_count += 1;
					is_count = true;
				}
				else
				{
					is_count = false;
					//temp_count = 0;
				}
			}
			else
			{
				if (temp_count != 0)
				{
					temp_count += 1;
				}
			}
		}
		if ((!is_count && temp_count > 10) || (i == scare - 1 && temp_count > 10))
		{
			if (number_of_information == 0)
			{
				number_of_information++;
				zero_lenth = temp_count;
				information += "0";
			}
			else
			{
				number_of_information++;
				if (temp_count >= 0.6 * zero_lenth && temp_count <= 1.5 * zero_lenth)
				{
					information += "0";
				}
				if (temp_count > 1.5 * zero_lenth)
				{
					information += "1";
				}
			}

		}
		if (!is_count)
		{
			temp_count = 0;
		}
	}
	return information;
}
//将图片转化成有效字符串信息
string Decode:: picture_to_string(Mat& image)
{
	Mat imageGray, imageGuussian;
	Mat imageSobelX, imageSobelY, imageSobelOut;

	//1. 原图像大小调整，提高运算效率 
	resize(image, image, Size(500,500));//500,500
	//imshow("1.原图像", image);

	//2. 转化为灰度图 
	cvtColor(image, imageGray, CV_RGB2GRAY);
	//imshow("2.灰度图", imageGray);

	//3. 高斯平滑滤波 
	GaussianBlur(imageGray, imageGuussian, Size(3, 3), 0);
	//imshow("3.高斯平衡滤波", imageGuussian);

	//4.求得水平和垂直方向灰度图像的梯度差,使用Sobel算子 
	Mat imageX16S, imageY16S;
	Sobel(imageGuussian, imageX16S, CV_16S, 1, 0, 3, 1, 0, 4);
	Sobel(imageGuussian, imageY16S, CV_16S, 0, 1, 3, 1, 0, 4);
	convertScaleAbs(imageX16S, imageSobelX, 1, 0);
	convertScaleAbs(imageY16S, imageSobelY, 1, 0);
	imageSobelOut = imageSobelX - imageSobelY;
	//imshow("4.X方向梯度", imageSobelX);
	//imshow("4.Y方向梯度", imageSobelY);
	//imshow("4.XY方向梯度差", imageSobelOut);

	//5.均值滤波，消除高频噪声 
	blur(imageSobelOut, imageSobelOut, Size(3, 3));
	//imshow("5.均值滤波", imageSobelOut);

	//6.二值化 
	Mat imageSobleOutThreshold;
	threshold(imageSobelOut, imageSobleOutThreshold, 180, 255, CV_THRESH_BINARY);
	//imshow("6.二值化", imageSobleOutThreshold);

	//7.闭运算，填充条形码间隙 
	Mat element = getStructuringElement(0, Size(7, 7));
	morphologyEx(imageSobleOutThreshold, imageSobleOutThreshold, MORPH_CLOSE, element);
	//imshow("7.闭运算", imageSobleOutThreshold);

	//8. 腐蚀，去除孤立的点 
	erode(imageSobleOutThreshold, imageSobleOutThreshold, element);
	//imshow("8.腐蚀", imageSobleOutThreshold);

	//9. 膨胀，填充条形码间空隙，根据核的大小，有可能需要2~3次膨胀操作 
	for (int i = 1; i <= 3; i++)
	{
		dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
	}
	//imshow("9.膨胀", imageSobleOutThreshold);
	vector<vector<Point>> contours;
	vector<Vec4i> hiera;

	//10.通过findContours找到条形码区域的矩形边界 
	findContours(imageSobleOutThreshold, contours, hiera, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	//new
	while (contours.size() > 1)
	{
		dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
		findContours(imageSobleOutThreshold, contours, hiera, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	}
	//end new




	//new
	if (contours.size() <= 0)
	{
		//cout << "图像存在错误，无法正确识别条码！" << endl;
		//system("pause");
		cout << "此处存在无法识别图片，忽略" << endl;
		return "";
	}


	cout << contours.size() << endl;
	Rect rect = boundingRect((Mat)contours[0]);
	rect.x = rect.x - (rect.width / 20);
	rect.width = rect.width * 1.1;
	Mat resultImag = Mat(image, rect);

	//rectangle(image, rect, Scalar(255), 2);//画蓝框,可以删掉

	//imshow("10.找出二维码矩形区域", image);

	//imshow("11.裁剪出二维码", resultImag);

	resize(resultImag, resultImag, Size(500, 500));

	//imshow("12.裁剪完改变大小", resultImag);


	//cout << "长度:" << resultImag.rows << "     " << "宽度:" << resultImag.cols << endl;
	int mid = resultImag.rows / 2;
	uchar* p = resultImag.ptr<uchar>(mid);



	//cout << endl;
	string infor = deal_pixel(p, resultImag.cols * 3);
	//cout << infor << endl;
	return infor;
}
//将字符串转成对应的ASCII码并且提供正误判断
int Decode::string_to_ascii(string infor_str)
{
	if (infor_str.length() != 10)
	{
		cout << "读到长度为:" << infor_str.length() <<"  的解码字符串，已忽略" <<endl;
		return -1;
	}
	if (infor_str == "0000000000"&&!is_start)
	{
		is_start = true;
		is_even_number = false;
		return 0;
	}
	if (infor_str == "0111111111" || infor_str == "1111111111")
	{
		is_end = true;
		is_start = false;
	}
	if (!is_start || is_end)
		return 0;
	if (infor_str[1] == '0' && is_even_number)
	{
		is_even_number = false;
		return count_ascii_value(infor_str);
	}
	else if (infor_str[1] == '1' && !is_even_number)
	{
		is_even_number = true;
		return count_ascii_value(infor_str);
	}
	return 0;

}
//具体计算ASCII值
int Decode::count_ascii_value(string str)
{
	int ans = 0;
	for (int i = 2; i <= 9; i++)
	{
		ans *= 2;
		ans += (int)str[i] -48;
	}
	return ans;

}
//将ASCII值变成字符，此处同时照应string_to_ascii中的正误判断
string Decode::ascii_to_word(int value)
{
	if (value == -1 || value == 0)
	{
		cout << "【跳过一张图片】" << endl;
		return "";
	}
	else
	{
		string temp_str = "";
		//cout << "此处字符为:" << (char)value<<"值为："<<value<<endl;
		temp_str += (char)value;
		return temp_str;
	}
	
}
string Decode::path;
string Decode::project_name;
bool Decode::is_even_number = true;
bool Decode::is_start = false;
bool Decode::is_end = false;