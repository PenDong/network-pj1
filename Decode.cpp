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
	cout << "�������ļ���ַ:(������ϡ�\\��)"<<endl;
	cin >> path;
	cv::String cv_path = path;//Ҫ����ͼƬ����·���ַ���������cv::String
	cout << "��������Ŀ��:" << endl;
	cin >> project_name;
	for(int i=0; ;i++)
	{
		string temp_path = path +project_name+ Code::to_string(i) + ".jpg";
		if (!is_picture_exist(temp_path))
			break;
		cv_path = temp_path;
		cout << "���ڶ�" << cv_path << "���в���" << endl;
		image = imread(cv_path);
		result_str += ascii_to_word(string_to_ascii(picture_to_string(image)));
	}
	cout << "����õ����Ϊ��" << endl;
	cout << result_str;
	if (!is_end)
		cout << "û�жȵ�����λ�����ܴ����쳣"<<endl;
	
}
//�ж��ļ��Ƿ����
bool Decode::is_picture_exist(string picture_name)
{
	ifstream f(picture_name.c_str());
	return f.good();
}
//�����ص�����㷨����
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
//��ͼƬת������Ч�ַ�����Ϣ
string Decode:: picture_to_string(Mat& image)
{
	Mat imageGray, imageGuussian;
	Mat imageSobelX, imageSobelY, imageSobelOut;

	//1. ԭͼ���С�������������Ч�� 
	resize(image, image, Size(500,500));//500,500
	//imshow("1.ԭͼ��", image);

	//2. ת��Ϊ�Ҷ�ͼ 
	cvtColor(image, imageGray, CV_RGB2GRAY);
	//imshow("2.�Ҷ�ͼ", imageGray);

	//3. ��˹ƽ���˲� 
	GaussianBlur(imageGray, imageGuussian, Size(3, 3), 0);
	//imshow("3.��˹ƽ���˲�", imageGuussian);

	//4.���ˮƽ�ʹ�ֱ����Ҷ�ͼ����ݶȲ�,ʹ��Sobel���� 
	Mat imageX16S, imageY16S;
	Sobel(imageGuussian, imageX16S, CV_16S, 1, 0, 3, 1, 0, 4);
	Sobel(imageGuussian, imageY16S, CV_16S, 0, 1, 3, 1, 0, 4);
	convertScaleAbs(imageX16S, imageSobelX, 1, 0);
	convertScaleAbs(imageY16S, imageSobelY, 1, 0);
	imageSobelOut = imageSobelX - imageSobelY;
	//imshow("4.X�����ݶ�", imageSobelX);
	//imshow("4.Y�����ݶ�", imageSobelY);
	//imshow("4.XY�����ݶȲ�", imageSobelOut);

	//5.��ֵ�˲���������Ƶ���� 
	blur(imageSobelOut, imageSobelOut, Size(3, 3));
	//imshow("5.��ֵ�˲�", imageSobelOut);

	//6.��ֵ�� 
	Mat imageSobleOutThreshold;
	threshold(imageSobelOut, imageSobleOutThreshold, 180, 255, CV_THRESH_BINARY);
	//imshow("6.��ֵ��", imageSobleOutThreshold);

	//7.�����㣬����������϶ 
	Mat element = getStructuringElement(0, Size(7, 7));
	morphologyEx(imageSobleOutThreshold, imageSobleOutThreshold, MORPH_CLOSE, element);
	//imshow("7.������", imageSobleOutThreshold);

	//8. ��ʴ��ȥ�������ĵ� 
	erode(imageSobleOutThreshold, imageSobleOutThreshold, element);
	//imshow("8.��ʴ", imageSobleOutThreshold);

	//9. ���ͣ������������϶�����ݺ˵Ĵ�С���п�����Ҫ2~3�����Ͳ��� 
	for (int i = 1; i <= 3; i++)
	{
		dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
	}
	//imshow("9.����", imageSobleOutThreshold);
	vector<vector<Point>> contours;
	vector<Vec4i> hiera;

	//10.ͨ��findContours�ҵ�����������ľ��α߽� 
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
		//cout << "ͼ����ڴ����޷���ȷʶ�����룡" << endl;
		//system("pause");
		cout << "�˴������޷�ʶ��ͼƬ������" << endl;
		return "";
	}


	cout << contours.size() << endl;
	Rect rect = boundingRect((Mat)contours[0]);
	rect.x = rect.x - (rect.width / 20);
	rect.width = rect.width * 1.1;
	Mat resultImag = Mat(image, rect);

	//rectangle(image, rect, Scalar(255), 2);//������,����ɾ��

	//imshow("10.�ҳ���ά���������", image);

	//imshow("11.�ü�����ά��", resultImag);

	resize(resultImag, resultImag, Size(500, 500));

	//imshow("12.�ü���ı��С", resultImag);


	//cout << "����:" << resultImag.rows << "     " << "���:" << resultImag.cols << endl;
	int mid = resultImag.rows / 2;
	uchar* p = resultImag.ptr<uchar>(mid);



	//cout << endl;
	string infor = deal_pixel(p, resultImag.cols * 3);
	//cout << infor << endl;
	return infor;
}
//���ַ���ת�ɶ�Ӧ��ASCII�벢���ṩ�����ж�
int Decode::string_to_ascii(string infor_str)
{
	if (infor_str.length() != 10)
	{
		cout << "��������Ϊ:" << infor_str.length() <<"  �Ľ����ַ������Ѻ���" <<endl;
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
//�������ASCIIֵ
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
//��ASCIIֵ����ַ����˴�ͬʱ��Ӧstring_to_ascii�е������ж�
string Decode::ascii_to_word(int value)
{
	if (value == -1 || value == 0)
	{
		cout << "������һ��ͼƬ��" << endl;
		return "";
	}
	else
	{
		string temp_str = "";
		//cout << "�˴��ַ�Ϊ:" << (char)value<<"ֵΪ��"<<value<<endl;
		temp_str += (char)value;
		return temp_str;
	}
	
}
string Decode::path;
string Decode::project_name;
bool Decode::is_even_number = true;
bool Decode::is_start = false;
bool Decode::is_end = false;