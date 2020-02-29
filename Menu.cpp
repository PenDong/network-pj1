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
	cout << "��ѡ���ܱ��:" << endl
		<< "����-----------------1" << endl
		<< "����-----------------2" << endl
		<< "�˳�-----------------0" << endl;
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
			cout << "��������ָ�����������:";
			break;
		}
		}
		if (!action)
		{
			break;
		}
		cout << "��ѡ���ܱ��:" << endl
			<< "����-----------------1" << endl
			<< "����-----------------2" << endl
			<< "�˳�-----------------0" << endl;
		cin >> action;
	}
}
