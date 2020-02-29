#include<iostream>
#include "core/core.hpp" 
#include "highgui/highgui.hpp" 
#include "imgproc/imgproc.hpp" 
#include<opencv.hpp>
#include"Menu.h"
#include"Code.h"
#include"Decode.h"
using namespace std;
using namespace cv;


void Menu::Go()
{
	int action;
	cout << "***********************Welcome*****************************" << endl
		<< "*********                                        **********";
	cout << "请选择功能编号:" << endl
		<< "编码-----------------1" << endl
		<< "解码-----------------2" << endl
		<< "退出-----------------0" << endl;
	cin >> action;
	while (action)
	{
		switch (action)
		{
		case 1:
		{
			Code::code();
			break;
		}
		case 2:
		{
			Decode::decode();
			break;
		}
		case 0:
		{
			break;
		}
		default:
		{
			cout << "输入错误的指令，请重新输入:";
			break;
		}
		}
		if (!action)
		{
			break;
		}
		cout << "请选择功能编号:" << endl
			<< "编码-----------------1" << endl
			<< "解码-----------------2" << endl
			<< "退出-----------------0" << endl;
		cin >> action;
	}
}
